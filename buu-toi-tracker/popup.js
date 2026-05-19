chrome.storage.local.get("buuTracker", (data) => {
  const tracker = data.buuTracker;
  const empty = document.getElementById("empty");
  const content = document.getElementById("content");
  if (!tracker || !tracker.summary) return;

  empty.hidden = true;
  content.hidden = false;

  const { summary, updatedAt, url } = tracker;
  const updated = new Date(updatedAt).toLocaleString();

  const a1Done  = summary.a1.solved;
  const a1Goal  = summary.a1.goal;
  const a1Need  = Math.max(0, a1Goal - a1Done);
  const a1Pct   = Math.min(100, (a1Done / a1Goal) * 100);
  const a23Done = summary.a23.solved;
  const a23Goal = summary.a23.goal;
  const a23Need = Math.max(0, a23Goal - a23Done);
  const a23Pct  = Math.min(100, (a23Done / a23Goal) * 100);
  const a1Met   = a1Done >= a1Goal;
  const a23Met  = a23Done >= a23Goal;

  const groups = Object.keys(summary.byGroup).sort();
  const groupHtml = groups
    .map((g) => {
      const gs = summary.byGroup[g];
      if (gs.countingTotal === 0) return "";
      const pct = (gs.countingSolved / gs.countingTotal) * 100;
      return `
        <div class="group">
          <div class="group-head">
            <strong>${g}</strong>
            <span>${gs.countingSolved}/${gs.countingTotal} counting</span>
          </div>
          <div class="group-bar"><div style="width:${pct}%"></div></div>
        </div>
      `;
    })
    .join("");

  content.innerHTML = `
    <div class="header">
      <div class="title">TOI Progress</div>
      <div class="updated">Updated ${updated}</div>
    </div>

    <div class="goals">
      <div class="goal ${a1Met ? "met" : ""}">
        <div class="goal-head">
          <span class="goal-name">A1 goal</span>
          <span class="goal-count">${a1Done} / ${a1Goal}</span>
        </div>
        <div class="goal-bar"><div style="width:${a1Pct}%"></div></div>
        <div class="goal-sub">${a1Met ? "✓ goal reached" : `${a1Need} more counting solves needed`}</div>
      </div>

      <div class="goal ${a23Met ? "met" : ""}">
        <div class="goal-head">
          <span class="goal-name">A2 + A3 goal</span>
          <span class="goal-count">${a23Done} / ${a23Goal}</span>
        </div>
        <div class="goal-bar"><div style="width:${a23Pct}%"></div></div>
        <div class="goal-sub">${a23Met ? "✓ goal reached" : `${a23Need} more counting solves needed`}</div>
      </div>
    </div>

    <h3>Counting tasks per group</h3>
    <div class="groups">${groupHtml}</div>

    <div class="meta">
      <span>Practice solved: ${summary.practiceSolved}/${summary.practiceTotal}</span>
      <span>Total: ${summary.solved}/${summary.total}</span>
    </div>

    <a class="cta" href="${url || "https://toi-coding.informatics.buu.ac.th/00-pre-toi"}" target="_blank">
      Open contest overview →
    </a>
  `;
});
