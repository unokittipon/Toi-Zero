# BUU TOI Progress Tracker (v2)

A Chrome extension for
[toi-coding.informatics.buu.ac.th/00-pre-toi](https://toi-coding.informatics.buu.ac.th/00-pre-toi)
that tracks the two passing goals separately:

- **A1 goal**: 20 counting tasks solved
- **A2 + A3 goal**: 20 counting tasks solved

## Practice vs counting

These tasks are **practice** and don't count toward passing:

- A1: even-numbered 002, 004, ..., 040 (20 tasks)
- A2: even-numbered 002, 004, ..., 032 (16 tasks)

Everything else counts:

- A1: odd 001..039 + all of 041..070
- A2: odd 001..031 + 033..062 (with the contest's natural gaps)
- A3: all 28 tasks

## What you see

When you open the contest overview page:

1. The score column on the task table is color-coded — green for solved, amber
   for partial, red for untouched. Practice rows are dimmed and italicized
   with a "· practice" tag on the task code.
2. A floating panel in the bottom-right shows:
   - Two **goal cards** (A1 and A2+A3) with a count, progress bar, and how
     many counting solves you still need. Cards turn green when the goal is met.
   - Stats row: Solved / Partial / To do / Practice.
   - Tabs: **To do (counting)** (default), **Partial**, **Solved**,
     **Practice**, **Groups**.
   - Each list entry is a direct link to that task's statement.
3. The toolbar popup mirrors the goal cards and a per-group counting summary
   from any page, using cached data.

## Install

1. Unzip the folder somewhere permanent.
2. Open `chrome://extensions`.
3. Toggle **Developer mode** on.
4. Click **Load unpacked** and pick the `buu-toi-tracker` folder.
5. Visit the contest overview page once you're logged in.

## Privacy

Runs only on `toi-coding.informatics.buu.ac.th`. Stores parsed progress in
`chrome.storage.local` (your machine only). No network requests, no analytics.

## If the rules change

Edit the top of `content.js`:

```js
function isPractice(group, num) {
  if (group === "A1" && num >= 2 && num <= 40 && num % 2 === 0) return true;
  if (group === "A2" && num >= 2 && num <= 32 && num % 2 === 0) return true;
  return false;
}
const A1_GOAL = 20;
const A23_GOAL = 20;
```

Then reload the extension at `chrome://extensions`.
