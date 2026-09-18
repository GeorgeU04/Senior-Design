# Device Test Plan — Schedule & Assignments

**Course:** CpE 191 / EEE 193B  
**Project:** Automated Hydroponic Garden (DWC)  
**Team:** Julia Daniliuk, Mariam Oudeh, George Umberger, Rainer Delos Santos  
**Testing start:** October 2026  

This schedule turns the Assignment 2 test IDs into a calendar. Work moves from **component verification → subsystem tests → integrated / long-run tests**.

---

## Ownership summary

| Person | Primary tests | Focus |
|--------|---------------|--------|
| **Mariam** | T1.0, T1.1, T1.2, T1.3, T6.0 | RGB/full-spectrum lighting + plant grow-out support |
| **Rainer** | T2.0, T2.1, T2.2, T3.0, T3.1, T6.0 | pH/TDS sensing + nutrient / pH dosing |
| **Julia** | T4.0, T4.1, T4.2, T6.0 | Reservoir climate (temp sensor + TEC cooler) |
| **George** | T5.0, T5.1, T6.0 | Touchscreen / GUI + system integration support |

**T6.0 (Autonomous Healthy Growing)** is a full-team test. Each person owns the subsystems they already verified; the whole team shares observation, logging, and pass/fail for the multi-day grow.

---

## Timeline overview

Spreadsheet-style Gantt (same layout as the project timeline):

**[Open Device Test Plan Timeline (HTML)](device-test-plan-timeline.html)** — open in a browser for Task Name · Bucket · weekly bars.

| Week starting | Phase | Who / what |
|---------------|-------|------------|
| **Oct 5** | Component | Mariam T1.1–T1.3 · Rainer T2.1–T2.2 · Julia T4.2 |
| **Oct 12** | Component | Rainer T3.1 · Julia T4.1 · Mariam wrap · George UI prep |
| **Oct 19** | Subsystem | Mariam T1.0 · Rainer T2.0 · George T5.0–T5.1 (starts) |
| **Oct 26** | Subsystem | Rainer T3.0 · Julia T4.0 · George T5 wrap |
| **Nov 2** | Integration | Full-team closed-loop dry run |
| **Nov 9** | Reliability | Low water, power cycle, overnight run |
| **Nov 16** | Long-run | T6.0 autonomous grow begins (through Dec 6) |
| **Dec 7** | Close-out | Test report and remaining fixes (through Dec 13) |

| Phase | Dates (2026) | Goal |
|-------|--------------|------|
| **1. Component** | Oct 5 – Oct 18 | Accuracy / actuation of sensors, pumps, cooler, light channels |
| **2. Subsystem** | Oct 19 – Nov 1 | Feature-level tests (T1.0–T5.1) against measurable requirements |
| **3. Integration** | Nov 2 – Nov 15 | Closed-loop growControl + fault cases (low water, power cycle) |
| **4. Long-run** | Nov 16 – Dec 6 | T6.0 autonomous grow (target ≥ 14–21 days) |
| **5. Close-out** | Dec 7 – Dec 13 | Fill test report, unresolved issues, prototype status |

*Exact weekdays can shift with lab access; keep the phase order.*

---

## Week-by-week plan

### Week of Oct 5 — Component kickoff

| Owner | Test ID | Work this week | Pass criterion (fill exact numbers before run) |
|-------|---------|----------------|-----------------------------------------------|
| Mariam | T1.1 | Blue channel on for extended run; log PWM / visual | Stays commanded PWM; on for photoperiod window |
| Mariam | T1.2 | Full-spectrum / white channel extended run | Same |
| Mariam | T1.3 | Red channel extended run | Same |
| Rainer | T2.1 | Calibrate / check pH in 7.00 and 10.00 buffers | Within **±0.1 pH** of reference |
| Rainer | T2.2 | TDS/EC in known nutrient mix | Within **±X%** of reference (set X before test) |
| Julia | T4.2 | DS18B20 vs reference thermometer (cold / ambient / warm) | Within **±X °C** of reference |

**Deliverable:** Component data sheets / log tables started for each test ID.

---

### Week of Oct 12 — Actuators

| Owner | Test ID | Work this week | Pass criterion |
|-------|---------|----------------|----------------|
| Rainer | T3.1 | Peristaltic pumps: command known mL of water; measure | Dispensed volume within **±X mL or ±X%** |
| Julia | T4.1 | TEC + circulation: verify cool-down over time | Water temp decreases; circuit reliable |
| Mariam | T1.x wrap | Finish any incomplete light-channel logs | Channels documented |
| George | Prep | Confirm UI build, list screens/buttons for T5.1 checklist | Checklist ready |

**Deliverable:** Pump calibration constants (ml/s) confirmed for dosing software if needed.

---

### Week of Oct 19 — Subsystem features (start)

| Owner | Test ID | Work this week | Pass criterion |
|-------|---------|----------------|----------------|
| Mariam | T1.0 | Stage-based RGB/PWM ratios for a selected plant profile | Ratios within **±5%** of stage targets for photoperiod |
| Rainer | T2.0 | Automated monitoring: hold / report pH 5.5–6.5 and plant EC/TDS band | Readings in band under steady conditions |
| George | T5.0 / T5.1 | Navigate plant select, home, settings; live values vs sensors | Required screens/buttons work; displayed values match sensors |

---

### Week of Oct 26 — Subsystem features (finish)

| Owner | Test ID | Work this week | Pass criterion |
|-------|---------|----------------|----------------|
| Rainer | T3.0 | Auto Micro → Grow → Bloom (or separate bottles); measure volume / TDS change | Volume within **±X mL / ±X%**; TDS moves toward target |
| Julia | T4.0 | Warm reservoir → cooler engages → return toward target | Cooler on at threshold; temp returns toward Tw within **X min** |
| George | T5.x wrap | Fix UI issues found week prior; retest checklist | 100% required UI paths pass |
| All | — | Sync logs; freeze “X” placeholders that are still open | Metrics locked for report |

---

### Week of Nov 2 — Integrated dry run

| Owner | Activity | Notes |
|-------|----------|--------|
| All | Run growControl with plant selected (e.g. Lettuce) | Lights + climate + chemistry enabled |
| Rainer | Watch pH/EC loops | Confirm no continuous over-dose |
| Julia | Watch cooler / air fans | Confirm hysteresis behavior |
| Mariam | Watch photoperiod / stage lights | Confirm on/off vs RTC |
| George | Watch UI live data during run | Spot mismatches |

**Fault mini-tests (same week or next):** low water → REFILL / dosing hold; power cycle recover.

---

### Week of Nov 9 — Reliability / abnormal conditions

| Condition | Expected | Owners |
|-----------|----------|--------|
| Water level below ADC gate | REFILL; new nutrient doses blocked | Rainer + George |
| Temperature step change | Fans / cooler respond per FSM | Julia + Mariam |
| Power cycle | Safe restart; sensors/UI recover | George + All |
| Extended overnight run | No unintended shutdown | All |

---

### Nov 16 – Dec 6 — T6.0 Autonomous Healthy Growing

| Item | Plan |
|------|------|
| Crop | Lettuce (or other profile agreed by team) |
| Duration | Target **≥ 14 days** continuous autonomous operation (stretch **21 days**) |
| Logging | Daily: pH, EC/TDS, water temp, enclosure temp, water level, lights on?, faults |
| Success | No unintended shutdown; measurable plant growth; chemistry/climate mostly in band |
| Roles | Each person monitors their subsystem; team shares daily check + end report |

---

### Week of Dec 7 — Close-out

- Complete test report tables (method, metric, result, pass/fail).
- List failures and firmware/hardware fixes still required for deployable prototype.
- Update prototype status section for the course deliverable.

---

## Master assignment matrix

| Test ID | Feature | Lead | Supporting | Target window |
|---------|---------|------|------------|---------------|
| T1.0 | Automated lighting by growth stage | Mariam | George (UI profile) | Oct 19–24 |
| T1.1 | Blue PWM endurance | Mariam | — | Oct 5–11 |
| T1.2 | Full-spectrum / white endurance | Mariam | — | Oct 5–11 |
| T1.3 | Red PWM endurance | Mariam | — | Oct 5–11 |
| T2.0 | Automated nutrient monitoring | Rainer | — | Oct 19–24 |
| T2.1 | pH sensor accuracy | Rainer | — | Oct 5–11 |
| T2.2 | TDS sensor accuracy | Rainer | — | Oct 5–11 |
| T3.0 | Automated nutrient dispensing | Rainer | — | Oct 26–31 |
| T3.1 | Peristaltic pump volume | Rainer | — | Oct 12–17 |
| T4.0 | Reservoir climate control | Julia | — | Oct 26–31 |
| T4.1 | TEC cooler actuation | Julia | — | Oct 12–17 |
| T4.2 | Temperature sensor accuracy | Julia | — | Oct 5–11 |
| T5.0 | Interactive plant / live data UI | George | Mariam (profile data) | Oct 19–31 |
| T5.1 | Touchscreen / menu coverage | George | — | Oct 19–31 |
| T6.0 | Autonomous healthy growing | **All** | — | Nov 16 – Dec 6 |

---

## Suggested lab equipment checklist

| Need | Used by |
|------|---------|
| pH 7.00 / 10.00 buffers + DI water | T2.1 |
| Reference TDS/EC meter or known mix | T2.2 |
| Graduated cylinder / scale for mL | T3.0, T3.1 |
| Reference thermometer | T4.0, T4.2 |
| Stopwatch / RTC log | T1.x, T6.0 |
| Serial console + UI | T5.x, integration |

---

## Notes for the report

1. Replace every **±X** in the original plan with a locked number **before** Phase 2 (recommend: volume ±10% or ±1 mL; TDS ±10%; temp ±1 °C; cool-down time based on first T4.1 run).
2. Lighting in firmware is **white / blue / red / NIR** (not classic RGB green). Map T1 wording to actual channels in the final report.
3. Heater path was removed from current firmware; T4 focuses on **cooler + fans** unless a heater is re-added.
4. Point detailed control behavior at [`growControl-state-machine.md`](growControl-state-machine.md) when describing automated tests.

---

## X. Conclusion — G. Device Test Plan

*(Paste-ready text for Assignment 2.)*

The device test plan defines how the team will verify that the automated deep water culture (DWC) hydroponic garden meets its measurable requirements before the deployable prototype is finalized. Semester one focused on designing, prototyping, and checking major components in isolation. The remaining work requires proving that sensors, actuators, and control software operate correctly together under realistic growing conditions.

Testing begins in October 2026 and proceeds in five phases. Phase 1 verifies individual sensors and actuators, including light-channel PWM endurance, pH and TDS accuracy, pump dispensed volume, temperature-sensor accuracy, and cooler actuation. Phase 2 evaluates feature-level behavior: stage-based lighting, automated nutrient monitoring and dispensing, reservoir climate control, and the touchscreen interface for plant selection and live data. Phase 3 integrates these subsystems through a closed-loop dry run of the grow-control state machine and checks abnormal cases such as low water level and power cycling. Phase 4 executes the full-team autonomous grow test (T6.0), targeting at least fourteen days of continuous operation with measurable plant growth. Phase 5 closes out the report by recording pass/fail results against acceptance criteria and listing any remaining hardware or firmware fixes.

Ownership is divided so each major deliverable has a clear lead: Mariam for lighting (T1.0–T1.3), Rainer for nutrient sensing and dosing (T2.0–T3.1), Julia for reservoir climate (T4.0–T4.2), and George for the user interface (T5.0–T5.1). The autonomous grow-out (T6.0) is shared by the whole team, with each member responsible for monitoring the subsystem they previously verified. Every test ID includes a method, metric, required equipment, responsible person, and scheduled window so results can be compared directly to the project feature set.

By progressing from component checks to subsystem features, integrated control, and extended autonomous operation, the plan determines which capabilities already satisfy design goals and which still need improvement. Completing this schedule will provide the evidence needed to judge readiness of the deployable prototype and to support a more water-efficient, lower-maintenance approach to small-scale indoor food production.
