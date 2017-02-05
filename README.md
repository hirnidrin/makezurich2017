# MakeZurich:GreenAgain
## Collecting Temperature and Humidity Open-data Helps Cactuseses to Grow Strong!

## Objective
Gruene Stadt Zurich is interested in learning about the possibility of using IoT technologies based on LoRa for monitoring gardens and public green spaces in the city of Zurich.
They envision a portable, compact data-collection unit that gardeners can easily pickup and place in their location of choice to monitor the environment. The data to be gathered, also called "garden state variables", are in order of priority:
 * Battery status: could alert the gardeners to recharge the units when running out of power);
 * Temperature;
 * Humidity;
 * Air flow / Wind: interesting for plants like orchids, which are particularly sensitive to currents and wind. 
Gardeners and other end-users will be able see the current state and a time-trace history of the "garden state variables" in a dedicated website, and download the data. The MakeZurich hackathon is a first-step opportunity to explore how digital non-intrusive monitoring system can be useful to increase the productivity of gardners and other personnel responsible for maintaining public green spaces in the city of Zurich.

## Location
The Sukkulentensamlung is composed of five greenhouses, which are about 10m long. The houses have poor electrical cabling connectivity and there is no internet connection readily available in place. Stadt Zurich IT network supplies the IT connectivity infrastructure to the faciity. Unfortunately, because of safety and security ground (which? investigate...), it is not possible to connect an untrasted untrusted gateway in the short term of the MakeZurich hackathon. The current infrastructure consists of data loggers that need to be read-out by physically connecting to PC via USB.

## Team
The Hackathon team is comosed by (... and their Slack ID are):
* Giorgio (@5igno): the guy with the soldering iron;
* Patrick (@citizenvice): working hard to show you the data;
* Philip (@philshem): thanks to him the sensor-node board is dry and safe ... and it looks great too!
* Quim (@quim_vilar): because you can become an expert in TTN netowrk coverage in 48 hours;
* Werner (@itsu): you need one like him to get thigs done! You really do!

We thank for the collaboration of (Slack ID):
* Jonas Heimgartner (@gszheo) Gruene Stadt Zurich
* Mr Schneider, gardener in chief at the Sukkulentensammlung Zurich
* Matthias Schiebli (@matt) at Sensirion for support with their sensors 

## Solution
We made a portable and compact open-data collection unit that gardners can easily pick up and place in the greenhouse of their choice.


## Todos for the team
In the long term:
* check stability, accuracy;
* analized end-user adoption.

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


