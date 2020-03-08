
#if !defined(SCIENTIFIC_DATA_H)
#define SCIENTIFIC_DATA_H

/* scientific constants */
const double pi{ 3.1415926535897932384626 };
const double G{ 6.6743e-11 };               // m**3 / (kg * s)
const double c{ 299792458 };                // m / s

/* basic clock data */
const int min_to_sec{ 60 };
const int hour_to_sec{ 3600 };
const int day_to_sec{ 86400 };

/* astronomical data (kg and m) */
const double sun_mass{ 1.98847e30 };
const double sun_radius{ 6.96342e8 };
const double earth_mass{ 5.9722e24 };
const double earth_radius{ 6.378e6 };
const double earth_sun_mean_dist{ 1.495978707e11 };
const double moon_mass{ 7.342e22 };
const double moon_radius{ 1.7374e6 };
const double earth_moon_mean_dist{ 3.84402e8 };

#endif
