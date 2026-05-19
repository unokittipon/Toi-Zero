// ==============================================================
// BUU TOI Progress Tracker — content script (v3)
//
// Behavior:
//  • On the overview page: parse the live task table and update cache.
//  • On every other page: render panel from cached snapshot, then
//    fetch the overview in the background to refresh.
//  • On task pages: also show a big floating "Download statement" button.
// ==============================================================

(function () {
  "use strict";

  // -----------------------------------------------------------
  // Configuration
  // -----------------------------------------------------------
  function isPractice(group, num) {
    if (group === "A1" && num >= 2 && num <= 40 && num % 2 === 0) return true;
    if (group === "A2" && num >= 2 && num <= 32 && num % 2 === 0) return true;
    return false;
  }
  const A1_GOAL = 20;
  const A23_GOAL = 20;
  const STORAGE_KEY = "buuTracker";

  // The contest path (e.g. "/00-pre-toi") — derived from the URL.
  // We assume the contest slug is the first path segment.
  const contestSlug = (location.pathname.split("/").filter(Boolean)[0]) || "00-pre-toi";
  const overviewUrl = `/${contestSlug}`;

  // -----------------------------------------------------------
  // Feature: Floating "Download statement" button on task pages
  // -----------------------------------------------------------
  const taskPageMatch = location.pathname.match(/\/tasks\/([A-Z0-9-]+)\/(description|submissions|statements)/i);
  if (taskPageMatch) {
    injectTaskPageDownloadButton(taskPageMatch[1]);
  }
  function injectTaskPageDownloadButton(taskCode) {
    if (document.getElementById("buu-tracker-task-dl")) return;
    const fab = document.createElement("a");
    fab.id = "buu-tracker-task-dl";
    fab.href = `/${contestSlug}/tasks/${taskCode}/statements/TH`;
    fab.download = `${taskCode}.pdf`;
    fab.title = "Download task statement (TH)";
    fab.innerHTML = `
      <svg width="18" height="18" viewBox="0 0 24 24" fill="none"
           stroke="currentColor" stroke-width="2.4" stroke-linecap="round" stroke-linejoin="round">
        <path d="M12 3v12m0 0l-5-5m5 5l5-5M5 21h14"/>
      </svg>
      <span>Download ${taskCode}</span>
    `;
    document.body.appendChild(fab);
  }

  // -----------------------------------------------------------
  // Parsing: turn a CMS overview Document into a snapshot.
  // Works for both `document` (current page, when on overview) and
  // a fetched HTML document (when on any other page).
  // -----------------------------------------------------------
  function parseOverview(doc) {
    const table = doc.querySelector("table.main_task_list");
    if (!table) return null;

    const tasks = [];
    table.querySelectorAll("tbody tr").forEach((row) => {
      const sc = row.querySelector("td.public_score");
      const cc = row.querySelector("th");
      const nc = row.querySelectorAll("td")[1];
      if (!sc || !cc) return;
      const code = cc.textContent.trim();
      const name = nc ? nc.textContent.trim() : "";
      const m = sc.textContent.match(/(\d+)\s*\/\s*(\d+)/);
      const score = m ? parseInt(m[1], 10) : 0;
      const max = m ? parseInt(m[2], 10) : 100;
      const status = score >= max ? "solved" : score === 0 ? "untouched" : "partial";
      const parts = code.split("-");
      const group = parts[0] || "?";
      const num = parseInt(parts[1], 10) || 0;
      const practice = isPractice(group, num);
      tasks.push({ code, name, score, max, status, group, num, practice });
    });

    const summary = computeSummary(tasks);
    return { updatedAt: Date.now(), url: location.origin + overviewUrl, tasks, summary };
  }

  function computeSummary(tasks) {
    const summary = {
      total: tasks.length, solved: 0, partial: 0, untouched: 0,
      practiceTotal: 0, practiceSolved: 0,
      a1:  { total: 0, solved: 0, partial: 0, untouched: 0, goal: A1_GOAL },
      a23: { total: 0, solved: 0, partial: 0, untouched: 0, goal: A23_GOAL },
      byGroup: {},
    };
    tasks.forEach((t) => {
      summary[t.status]++;
      if (t.practice) {
        summary.practiceTotal++;
        if (t.status === "solved") summary.practiceSolved++;
      } else {
        const b = t.group === "A1" ? "a1" : "a23";
        summary[b].total++;
        summary[b][t.status]++;
      }
      if (!summary.byGroup[t.group]) {
        summary.byGroup[t.group] = {
          total: 0, solved: 0, partial: 0, untouched: 0,
          countingTotal: 0, countingSolved: 0,
        };
      }
      const g = summary.byGroup[t.group];
      g.total++;
      g[t.status]++;
      if (!t.practice) {
        g.countingTotal++;
        if (t.status === "solved") g.countingSolved++;
      }
    });
    return summary;
  }

  // -----------------------------------------------------------
  // Storage helpers
  // -----------------------------------------------------------
  function saveSnapshot(snapshot) {
    if (chrome?.storage?.local) {
      chrome.storage.local.set({ [STORAGE_KEY]: snapshot });
    }
  }
  function loadSnapshot(callback) {
    if (chrome?.storage?.local) {
      chrome.storage.local.get(STORAGE_KEY, (data) => callback(data[STORAGE_KEY] || null));
    } else {
      callback(null);
    }
  }

  // -----------------------------------------------------------
  // Background fetch: get the overview HTML and parse it.
  // Same-origin, uses the user's session cookies, no auth needed.
  // -----------------------------------------------------------
  async function fetchOverviewSnapshot() {
    try {
      const res = await fetch(overviewUrl, { credentials: "same-origin" });
      if (!res.ok) return null;
      const html = await res.text();
      const doc = new DOMParser().parseFromString(html, "text/html");
      return parseOverview(doc);
    } catch (err) {
      console.warn("[BUU Tracker] failed to fetch overview:", err);
      return null;
    }
  }

  // -----------------------------------------------------------
  // Main flow
  // -----------------------------------------------------------
  // 1. If we're on the overview page, parse it directly and decorate
  //    the live table rows with status colors.
  const liveSnapshot = parseOverview(document);
  if (liveSnapshot) {
    decorateTable(liveSnapshot.tasks);
    saveSnapshot(liveSnapshot);
    renderPanel(liveSnapshot);
    return;
  }

  // 2. Otherwise: show cached snapshot immediately (if any),
  //    then refresh from the network in the background.
  loadSnapshot((cached) => {
    if (cached && cached.summary) {
      renderPanel(cached, { stale: true });
    } else {
      renderPanel(null);
    }
    fetchOverviewSnapshot().then((fresh) => {
      if (!fresh) return;
      saveSnapshot(fresh);
      renderPanel(fresh);
    });
  });

  // -----------------------------------------------------------
  // Decorate the live overview table (status colors etc.)
  // -----------------------------------------------------------
  function decorateTable(tasks) {
    const table = document.querySelector("table.main_task_list");
    if (!table) return;
    const byCode = {};
    tasks.forEach((t) => (byCode[t.code] = t));
    table.querySelectorAll("tbody tr").forEach((row) => {
      const cc = row.querySelector("th");
      if (!cc) return;
      const t = byCode[cc.textContent.trim()];
      if (!t) return;
      row.classList.add("buu-tracker-row", `buu-tracker-${t.status}`);
      if (t.practice) row.classList.add("buu-tracker-practice");
    });
  }

  // -----------------------------------------------------------
  // Render the floating panel.
  // -----------------------------------------------------------
  let panelEl = null;

  function renderPanel(snapshot, opts) {
    opts = opts || {};

    // First render: build skeleton.
    if (!panelEl) {
      panelEl = document.createElement("div");
      panelEl.id = "buu-tracker-panel";
      document.body.appendChild(panelEl);
      // Restore collapsed state.
      if (localStorage.getItem("buuTrackerCollapsed") === "1") {
        panelEl.classList.add("collapsed");
      }
    }

    if (!snapshot || !snapshot.summary) {
      panelEl.innerHTML = `
        <div class="buu-tracker-header">
          <div class="buu-tracker-title">
            <span class="buu-tracker-dot"></span>
            TOI Progress
          </div>
          <button class="buu-tracker-toggle" type="button" aria-label="Toggle">−</button>
        </div>
        <div class="buu-tracker-body">
          <div class="buu-tracker-loading">
            <div>Loading progress…</div>
            <div class="buu-tracker-loading-sub">Fetching the contest overview</div>
          </div>
        </div>
      `;
      wireToggle();
      return;
    }

    const s = snapshot.summary;
    const a1Done  = s.a1.solved;
    const a1Need  = Math.max(0, A1_GOAL - a1Done);
    const a1Pct   = Math.min(100, (a1Done / A1_GOAL) * 100);
    const a23Done = s.a23.solved;
    const a23Need = Math.max(0, A23_GOAL - a23Done);
    const a23Pct  = Math.min(100, (a23Done / A23_GOAL) * 100);
    const a1Met   = a1Done >= A1_GOAL;
    const a23Met  = a23Done >= A23_GOAL;
    const allMet  = a1Met && a23Met;

    const isOverview = !!parseOverview(document); // true when we're actually on the overview
    const staleTag = (opts.stale && !isOverview)
      ? `<span class="buu-tracker-stale" title="Cached snapshot — refreshing">cached</span>`
      : "";

    panelEl.innerHTML = `
      <div class="buu-tracker-header">
        <div class="buu-tracker-title">
          <span class="buu-tracker-dot ${allMet ? "win" : ""}"></span>
          TOI Progress
          ${staleTag}
        </div>
        <button class="buu-tracker-toggle" type="button" aria-label="Toggle">−</button>
      </div>
      <div class="buu-tracker-body">

        <div class="buu-tracker-goals">
          <div class="buu-tracker-goal ${a1Met ? "met" : ""}">
            <div class="buu-tracker-goal-head">
              <span class="buu-tracker-goal-name">A1 goal</span>
              <span class="buu-tracker-goal-count">${a1Done} / ${A1_GOAL}</span>
            </div>
            <div class="buu-tracker-goal-bar">
              <div style="width:${a1Pct}%"></div>
            </div>
            <div class="buu-tracker-goal-sub">
              ${a1Met ? "✓ goal reached" : `${a1Need} more counting solves needed`}
            </div>
          </div>

          <div class="buu-tracker-goal ${a23Met ? "met" : ""}">
            <div class="buu-tracker-goal-head">
              <span class="buu-tracker-goal-name">A2 + A3 goal</span>
              <span class="buu-tracker-goal-count">${a23Done} / ${A23_GOAL}</span>
            </div>
            <div class="buu-tracker-goal-bar">
              <div style="width:${a23Pct}%"></div>
            </div>
            <div class="buu-tracker-goal-sub">
              ${a23Met ? "✓ goal reached" : `${a23Need} more counting solves needed`}
            </div>
          </div>
        </div>

        <div class="buu-tracker-stats">
          <div class="buu-tracker-stat solved">
            <span class="buu-tracker-num">${s.solved}</span>
            <span class="buu-tracker-label">Solved</span>
          </div>
          <div class="buu-tracker-stat partial">
            <span class="buu-tracker-num">${s.partial}</span>
            <span class="buu-tracker-label">Partial</span>
          </div>
          <div class="buu-tracker-stat untouched">
            <span class="buu-tracker-num">${s.untouched}</span>
            <span class="buu-tracker-label">To do</span>
          </div>
          <div class="buu-tracker-stat practice">
            <span class="buu-tracker-num">${s.practiceSolved}/${s.practiceTotal}</span>
            <span class="buu-tracker-label">Practice</span>
          </div>
        </div>

        <div class="buu-tracker-tabs">
          <button class="buu-tracker-tab active" data-tab="todo-counting">To do</button>
          <button class="buu-tracker-tab" data-tab="partial">Partial</button>
          <button class="buu-tracker-tab" data-tab="solved">Solved</button>
          <button class="buu-tracker-tab" data-tab="practice">Practice</button>
          <button class="buu-tracker-tab" data-tab="groups">Groups</button>
        </div>

        <div class="buu-tracker-subtabs" data-subtabs>
          <button class="buu-tracker-subtab active" data-sub="ALL">All</button>
          <button class="buu-tracker-subtab" data-sub="A1">A1</button>
          <button class="buu-tracker-subtab" data-sub="A2">A2</button>
          <button class="buu-tracker-subtab" data-sub="A3">A3</button>
        </div>

        <div class="buu-tracker-list" data-list></div>
      </div>
    `;

    wireToggle();
    wireTabs(snapshot);
    renderList(snapshot, currentTab, currentSub);
  }

  function wireToggle() {
    const btn = panelEl.querySelector(".buu-tracker-toggle");
    if (!btn) return;
    btn.textContent = panelEl.classList.contains("collapsed") ? "+" : "−";
    btn.addEventListener("click", () => {
      panelEl.classList.toggle("collapsed");
      const collapsed = panelEl.classList.contains("collapsed");
      btn.textContent = collapsed ? "+" : "−";
      localStorage.setItem("buuTrackerCollapsed", collapsed ? "1" : "0");
    });
  }

  // Current UI state, persisted in localStorage so it survives tab switches/reloads.
  const TABS_WITH_SUBGROUPS = new Set(["todo-counting", "partial", "solved", "practice"]);
  let currentTab = localStorage.getItem("buuTrackerTab") || "todo-counting";
  let currentSub = localStorage.getItem("buuTrackerSub") || "ALL";

  function wireTabs(snapshot) {
    const tabs = panelEl.querySelectorAll(".buu-tracker-tab");
    const subEls = panelEl.querySelectorAll(".buu-tracker-subtab");
    const subBar = panelEl.querySelector("[data-subtabs]");

    // Restore the previously active tab/sub on (re)render.
    tabs.forEach((t) => t.classList.toggle("active", t.dataset.tab === currentTab));
    subEls.forEach((s) => s.classList.toggle("active", s.dataset.sub === currentSub));
    if (subBar) subBar.style.display = TABS_WITH_SUBGROUPS.has(currentTab) ? "" : "none";

    tabs.forEach((tab) => {
      tab.addEventListener("click", () => {
        currentTab = tab.dataset.tab;
        localStorage.setItem("buuTrackerTab", currentTab);
        tabs.forEach((t) => t.classList.toggle("active", t === tab));
        if (subBar) subBar.style.display = TABS_WITH_SUBGROUPS.has(currentTab) ? "" : "none";
        renderList(snapshot, currentTab, currentSub);
      });
    });

    subEls.forEach((sub) => {
      sub.addEventListener("click", () => {
        currentSub = sub.dataset.sub;
        localStorage.setItem("buuTrackerSub", currentSub);
        subEls.forEach((s) => s.classList.toggle("active", s === sub));
        renderList(snapshot, currentTab, currentSub);
      });
    });
  }

  function renderList(snapshot, kind, sub) {
    const listEl = panelEl.querySelector("[data-list]");
    if (!listEl) return;
    const tasks = snapshot.tasks || [];
    const summary = snapshot.summary;

    if (kind === "groups") {
      const groups = Object.keys(summary.byGroup).sort();
      listEl.innerHTML = groups.map((g) => {
        const gs = summary.byGroup[g];
        const cPct = gs.countingTotal === 0 ? 0 : (gs.countingSolved / gs.countingTotal) * 100;
        const cPctTxt = gs.countingTotal === 0 ? "—" : cPct.toFixed(0) + "%";
        return `
          <div class="buu-tracker-group-row">
            <div class="buu-tracker-group-head">
              <strong>${g}</strong>
              <span>${gs.countingSolved}/${gs.countingTotal} counting · ${cPctTxt}</span>
            </div>
            <div class="buu-tracker-group-bar">
              <div style="width:${cPct}%"></div>
            </div>
            <div class="buu-tracker-group-sub">
              ${gs.solved} solved · ${gs.partial} partial · ${gs.untouched} to do
            </div>
          </div>
        `;
      }).join("");
      return;
    }

    let filtered;
    if (kind === "todo-counting") {
      filtered = tasks.filter((t) => !t.practice && t.status === "untouched");
    } else if (kind === "practice") {
      filtered = tasks.filter((t) => t.practice);
    } else {
      filtered = tasks.filter((t) => t.status === kind);
    }

    // Sub-group filter (A1 / A2 / A3 / ALL).
    if (sub && sub !== "ALL") {
      filtered = filtered.filter((t) => t.group === sub);
    }

    // Stable sort: by group, then by task number.
    filtered.sort((a, b) => a.group.localeCompare(b.group) || a.num - b.num);

    if (filtered.length === 0) {
      listEl.innerHTML = `<div class="buu-tracker-empty">Nothing here.</div>`;
      return;
    }

    // Icons.
    const stmtIcon = `<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.4" stroke-linecap="round" stroke-linejoin="round"><path d="M14 3H6a2 2 0 0 0-2 2v14a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V9z"/><path d="M14 3v6h6"/><path d="M8 13h8M8 17h6"/></svg>`;
    const submitIcon = `<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.4" stroke-linecap="round" stroke-linejoin="round"><path d="M5 4l14 8-14 8V4z"/></svg>`;
    const dlIcon = `<svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.4" stroke-linecap="round" stroke-linejoin="round"><path d="M12 3v12m0 0l-5-5m5 5l5-5M5 21h14"/></svg>`;

    listEl.innerHTML = filtered.map((t) => {
      const stmtHref = `/${contestSlug}/tasks/${t.code}/description`;
      const submitHref = `/${contestSlug}/tasks/${t.code}/submissions`;
      const dlHref = `/${contestSlug}/tasks/${t.code}/statements/TH`;
      const score = t.status === "partial" ? `${t.score}/${t.max}` : "";
      const cls = `buu-tracker-item-${t.status}` + (t.practice ? " buu-tracker-item-practice" : "");
      const tag = t.practice ? `<span class="buu-tracker-tag">practice</span>` : "";
      return `
        <div class="buu-tracker-row-wrap ${cls}">
          <a class="buu-tracker-item" href="${stmtHref}">
            <span class="buu-tracker-code">${t.code}</span>
            <span class="buu-tracker-name">${escapeHtml(t.name)}</span>
            ${tag}
            ${score ? `<span class="buu-tracker-score">${score}</span>` : ""}
          </a>
          <a class="buu-tracker-action buu-tracker-action-stmt" href="${stmtHref}"
             title="Open statement page" aria-label="Open statement page">
            ${stmtIcon}
          </a>
          <a class="buu-tracker-action buu-tracker-action-submit" href="${submitHref}"
             title="Open submissions / submit page" aria-label="Open submit page">
            ${submitIcon}
          </a>
          <a class="buu-tracker-action buu-tracker-action-dl" href="${dlHref}" download="${t.code}.pdf"
             title="Download statement PDF (TH)" aria-label="Download statement PDF">
            ${dlIcon}
          </a>
        </div>
      `;
    }).join("");
  }

  function escapeHtml(s) {
    return s.replace(/[&<>"']/g, (c) => ({
      "&": "&amp;", "<": "&lt;", ">": "&gt;",
      '"': "&quot;", "'": "&#39;",
    }[c]));
  }
})();
