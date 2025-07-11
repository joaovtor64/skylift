import process from 'node:process';
import wigle from "./wigle.js"
import guestimate from './guestimate.js';


const lat = parseFloat(process.argv[2].split("@")[1].split(",")[0])
const long =parseFloat(process.argv[2].split("@")[1].split(",")[1])

console.log()
await wigle(lat,long)

//Here we can either pick an existing ap point or middle of the box
await guestimate(lat+0.00000005,long+0.00000005)