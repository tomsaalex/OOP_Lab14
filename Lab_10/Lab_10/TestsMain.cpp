#include "TestsMain.h"
#include "TestsDomain.h"
#include "TestsRepository.h"
#include "TestFileRepository.h"
#include "TestsService.h"
#include "TestNotificationList.h"

void testAll()
{
	runAllDomainTests();
	runAllRepoTests();
	runAllFileRepoTests();
	runAllNotificationListTests();
	runAllServiceTests();
}