#include <unistd.h>
#include "riot_subscription_manager_sdds_impl.h"

int main()
{
	DDS_ReturnCode_t ret;

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}
	Log_setLvl(4);  // Disable logs, set to 0 for to see everything.

    for (;;) {
        sleep (10);
    }

    return 0;
}