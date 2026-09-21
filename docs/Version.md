# Version Documentation
## Version Macros
### LIBDUSTBUNNY_BERSION_XXXXX
```c
#define LIBDUSTBUNNY_VERSION_MAJOR	0
#define LIBDUSTBUNNY_VERSION_MINOR	1
#define LIBDUSTBUNNY_VERSION_PATCH	0
```
These macros are the version numbers for the MAJOR, MINOR and PATCH versions.
Libdustbunny follows the Semantic Versioning specification.
You can the SemVer spec at https://semver.org/

For a quick break-down:
	- Increment MAJOR version when backwards-incompatible changes are made.
	- Increment MINOR version when backwards-compatible changed or features are made.
	- Increment PATCH version when backwards-compatible bug fixes are made.

### Other
```c
#define LIBDUSTBUNNY_RELEASE_YEAR	2026
#define LIBDUSTBUNNY_AUTHOR			"Rory Lane"
#define LIBDUSTBUNNY_LICENSE		"MIT"
#define LIBDUSTBUNNY_REPO			"https://github.com/dot-underscore1703/dustbunny/libdustbunny"
#define LIBDUSTBUNNY_LICENSE_URL	"https://opensource.org/license/mit"
```
These macros should be fairly self explanatory.
- RELEASE_YEAR
	The year that the version of libdustbunny was made or released.

- AUTHOR
	The names of those who authored the version of libdustbunny.

- LICENSE
	The license that the version of libdustbunny is licensed under

- REPO
	The link to the Git repoistory of the version of libdustbunny.

- LICENSE_URL
	- A link where people can read the license that the version of libdustbunny	was licensed under.

