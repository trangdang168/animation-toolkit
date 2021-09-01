[ANGLE, POINT, SUMACC, HANDP, HANDS, KINE, SUMTOR] = textread('p01_INTRODUCTION_metrics.txt', '%f,%f,%f,%f,%f,%f,%f');
% {'angleDistance','pointDistance','sumSquaredAcc','handPotentialEnergy','handSpeed','kineticEnergy','sumTorques'});

summaryStats(ANGLE, "Sum of angle differences", "Counts", "Radians");
summaryStats(POINT, "Sum of point differences", "Counts", "Distance (meters)");
summaryStats(log(SUMACC), "Sum of squared accelerations (log scale)", "Counts", "(meters/s^2)^2");
summaryStats(HANDP, "Sum of left/right hand potential energy", "Counts", "Joules");
summaryStats(HANDS, "Sum of left/right hand speeds", "Counts", "meters/second");
summaryStats(log(KINE), "Kinetic energy (log)", "Counts", "Joules");
summaryStats(KINE, "Kinetic energy", "Counts", "Joules");
summaryStats(log(SUMTOR(SUMTOR> 0)), "Sum of squared torques (log)", "Counts", "(Newton meters)^2");



