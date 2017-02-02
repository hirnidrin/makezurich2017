# MakeZurich 2017 City Gardens Challenge -- Sukkulentensammlung

## Contacts
* Mr Jonas Heimgartner -- stakeholder Stadt Zürich
* Mr Schneider -- chief gardener at Sukkulentensammlung
* Hackathon team -- Giorgio, Patrick, Philip, Quim, Werner

## Situation
* 5 greenhouses, each about 10m long
* poor electrical cabling
* no internet connection readily available (garden office goes thru Stadt Zurich IT network, too closed for hooking up an untrusted gateway short term)
* currently they have some old-school data loggers that only can be read-out by connecting a PC with USB cable
* They participate in MZ17 to learn about the possibilities of Lora backed data acquisition / interaction. Check stability, accuracy, end user adoption. Convince end users / low-tech gardeners that modern digital non-intrusive monitoring system might be useful ;-)

## Goal
As agreed on phone call with Mr Heimgartner 31.1.2017
* One portable, compact data collection unit that gardeners can easily pickup and place in the greenhouse they choose. Right now it is no goal to have a fix installation in each greenhouse.
* Unit runs on battery / rechargable, hopefully "more than one week".
* Sensor values
 * Temp and humidity -- most interesting, do now.
 * Micro airflow -- postpone. Interesting for orchid collection... orchids don't like wind. Don't know if orchids are in a separate greenhouse.
* Reporting
 * End users / low-tech gardeners shall be able to open a website and see histogram and current value of temp and humidity.
 * Data download -- nice to have, not required by now.

## Todos for the team
* Check TTN LoraWAN coverage Mythenquai. If not ok:
 * search community for someone living close by for placing a temporary gateway.
 * Worst case: Place a GSM based gateway locally somewhere in the Sukkulentensammlung.
* Electronics / Arduino
 * Autonomous power supply: need a battery / rechargeable solution
  * - Minimal: Battery.
  * - Realistic: MicroUSB charger / mobile phone power bank.
  * - Ideal: solar panel charger / LiPo, but not sure if enough light. HW platform probably too power hungry, would need other processor  unit.
* SCRAPPED ~~Install and read a 5-position (or more) turn switch, so gardener can easily set the greenhouse where the box is currently located. This is used to not mess up the histograms.~~
* Measure power usage, minimize for longer batt life.
 * Switch off the green power LED. According schematics, uses about 5mA all the time.
 * SW sleep modes?
* Temp / humidity sensor integration, as in the works.
* Unit / box -- pack the thing so it is easily portable and usable. Openings for 
 * mechanical power switch -- push-release button with water protection?
 * micro USB charger connection
 * antenna RMA connector
 * combined temp / hum sensor... how where?
  * - fix mount based on box, some cm apart from box?
  * - just hanging at the 1m cable, for free placement?
  * - SCRAPPED ~~5-position turn switch, clearly labeled~~
* TTN
 * define data format
 * bring in the data
 * check handlers / how the get data out to storage / DB
* Reporting
 * simple unprotected webpage that can be set as bookmark / browser start page


