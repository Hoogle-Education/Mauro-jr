// Execute (1,10) => wait = 0, curTume = 11;
// Execute (7,5) => wait = 0 + 11-7 = 4, curTime = 11+5 = 16;
// Execute (6,10) => wait = 4 + 16-6 = 14, curTime = 16+10 = 26;
// Execute (5,15) => wait = 14 + 26-5 = 35, curTime = 26+15 = 41;
// Execute (42, 10) => wait = 14 + 26-5 = 35, curTime = 26+15 = 41;
// Execute (46, 10) => wait = 14 + 26-5 = 35, curTime = 26+15 = 41;
// Execute (44, 5) => wait = 14 + 26-5 = 35, curTime = 26+15 = 41;