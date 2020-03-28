
#if !defined(SCIENTIFIC_DATA_H)
#define SCIENTIFIC_DATA_H

// TODO: Probably I should be using km, not meters.

/* scientific constants */
const double pi{ 3.1415926535897932384626 };
const double G{ 6.6743e-11 };               // m**3 / (kg * s)
const double c{ 299792458 };                // m / s

/* basic clock data */
const int min_to_sec{ 60 };
const int hour_to_sec{ 3600 };
const int day_to_sec{ 86400 };
const int year_to_sec{ 31557600 };

#endif

