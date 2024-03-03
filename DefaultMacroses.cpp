#pragma once
#ifndef _DEFAULT_MACROSES_
#define _DEFAULT_MACROSES_

//AnimalDecreaseStep means that what will be added to the animal's DecreaseStep table in corresponding field.
// All numbers should be in range of [-1;1]. Otherwise you'll get lerp() of given number

//Day catagory
#define _DEFAULT_MORNING_AnimalDecreaseStep_hungerDecrease_ -0.05
#define _DEFAULT_MORNING_AnimalDecreaseStep_libidoDecrease_ 0.05
#define _DEFAULT_MORNING_AnimalDecreaseStep_ageDecrease_ 0

#define _DEFAULT_MORNING_AnimalSettings_viewDistance_ 1

#define _DEFAULT_NIGHT_AnimalDecreaseStep_hungerDecrease_ 0.05
#define _DEFAULT_NIGHT_AnimalDecreaseStep_libidoDecrease_ -0.05
#define _DEFAULT_NIGHT_AnimalDecreaseStep_ageDecrease_ 0

#define _DEFAULT_NIGHT_AnimalSettings_viewDistance_ -1

//Season catagory
#define _DEFAULT_SUMMER_AnimalDecreaseStep_hungerDecrease_ 0.08
#define _DEFAULT_SUMMER_AnimalDecreaseStep_libidoDecrease_ -0.1
#define _DEFAULT_SUMMER_AnimalDecreaseStep_ageDecrease_ 0

#define _DEFAULT_SUMMER_AnimalSettings_viewDistance_ 1

#define _DEFAULT_AUTOMN_AnimalDecreaseStep_hungerDecrease_ 0.03
#define _DEFAULT_AUTOMN_AnimalDecreaseStep_libidoDecrease_ -0.03
#define _DEFAULT_AUTOMN_AnimalDecreaseStep_ageDecrease_ 0

#define _DEFAULT_AUTOMN_AnimalSettings_viewDistance_ 0

#define _DEFAULT_WINTER_AnimalDecreaseStep_hungerDecrease_ 0.06
#define _DEFAULT_WINTER_AnimalDecreaseStep_libidoDecrease_ -0.15
#define _DEFAULT_WINTER_AnimalDecreaseStep_ageDecrease_ 0

#define _DEFAULT_WINTER_AnimalSettings_viewDistance_ -2

#define _DEFAULT_SPRING_AnimalDecreaseStep_hungerDecrease_ -0.1
#define _DEFAULT_SPRING_AnimalDecreaseStep_libidoDecrease_ -0.15
#define _DEFAULT_SPRING_AnimalDecreaseStep_ageDecrease_ 0

#define _DEFAULT_SPRING_AnimalSettings_viewDistance_ 0

//Extra catagory
#define _DEFAULT_SUNNY_AnimalDecreaseStep_hungerDecrease_ 0
#define _DEFAULT_SUNNY_AnimalDecreaseStep_libidoDecrease_ 0
#define _DEFAULT_SUNNY_AnimalDecreaseStep_ageDecrease_ 0

#define _DEFAULT_SUNNY_AnimalSettings_viewDistance_ 1

#define _DEFAULT_RAIN_AnimalDecreaseStep_hungerDecrease_ 0
#define _DEFAULT_RAIN_AnimalDecreaseStep_libidoDecrease_ 0.4
#define _DEFAULT_RAIN_AnimalDecreaseStep_ageDecrease_ 0

#define _DEFAULT_RAIN_AnimalSettings_viewDistance_ -1

#define _DEFAULT_
#define _DEFAULT_
#define _DEFAULT_
#define _DEFAULT_


#endif