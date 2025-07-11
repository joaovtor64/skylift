
import geolib from 'geolib';
import fs from "fs/promises"

// Define two geolocations (latitude, longitude)




async function guestimate(lat, long) {
    const point = { latitude: lat, longitude: long };
    function getpower(rssi) {
/**
 * WIFI_POWER_21dBm = 84,      // 21dBm
  WIFI_POWER_20_5dBm = 82,    // 20.5dBm
  WIFI_POWER_20dBm = 80,      // 20dBm
  WIFI_POWER_19_5dBm = 78,    // 19.5dBm
  WIFI_POWER_19dBm = 76,      // 19dBm
  WIFI_POWER_18_5dBm = 74,    // 18.5dBm
  WIFI_POWER_17dBm = 68,      // 17dBm
  WIFI_POWER_15dBm = 60,      // 15dBm
  WIFI_POWER_13dBm = 52,      // 13dBm
  WIFI_POWER_11dBm = 44,      // 11dBm
  WIFI_POWER_8_5dBm = 34,     // 8.5dBm
  WIFI_POWER_7dBm = 28,       // 7dBm
  WIFI_POWER_5dBm = 20,       // 5dBm
  WIFI_POWER_2dBm = 8,        // 2dBm
  WIFI_POWER_MINUS_1dBm = -4  // -1dBm
 */
        let arr=[
            84,82,80,78,76,74,68,60,52,44,34,28,20,8,-4
        ]
        return arr.reduce((prev, curr) =>
          Math.abs(curr - rssi) < Math.abs(prev - rssi) ? curr : prev
        );
      }
      
      
      
    function rssi(lat, long) {
        let distance = geolib.getDistance(point, { latitude: lat, longitude: long });
        if (distance < 1) {
            console.log("DISTANCE:" + distance)
            distance = 1
        }
        return (-40 - 10 * Math.log10(distance))
    }
    let output = { filename: "wtf", wifi: [] }
    let scan = JSON.parse(await fs.readFile("scan.json", "utf8"))
    for (let i in scan.results) {
        scan.results[i].rssi = rssi(scan.results[i].trilat, scan.results[i].trilong)
        scan.results[i].bssid = scan.results[i].netid

        delete scan.results[i].trilat
        delete scan.results[i].trilong
        delete scan.results[i].qos
        delete scan.results[i].transid
        delete scan.results[i].firsttime
        delete scan.results[i].lasttime
        delete scan.results[i].lastupdt
        delete scan.results[i].netid
        delete scan.results[i].name
        delete scan.results[i].type
        delete scan.results[i].comment
        delete scan.results[i].wep
        delete scan.results[i].bcninterval
        delete scan.results[i].frequency
        delete scan.results[i].rcois
        delete scan.results[i].encryption
        delete scan.results[i].country
        delete scan.results[i].region
        delete scan.results[i].road
        delete scan.results[i].city
        delete scan.results[i].housenumber
        delete scan.results[i].postalcode
        delete scan.results[i].freenet
        delete scan.results[i].dhcp
        delete scan.results[i].paynet
        delete scan.results[i].userfound


        if (scan.results[i].channel < 12&&scan.results[i].ssid) {
            
            output.wifi.push(scan.results[i])
        }


    }

    scan.results = scan.results.sort(function f(a, b) { return a.rssi - b.rssi })
    output.wifi = output.wifi.sort(function f(a, b) { return a.rssi - b.rssi })
    let min = scan.results[0].rssi
    let max = scan.results[scan.results.length - 1].rssi


    for(let i in output.wifi){

        
        //from -4 to 84
console.log(getpower((output.wifi[i].rssi-min)*(88)/(max-min)-4))
        output.wifi[i].power=getpower((output.wifi[i].rssi-min)*(88)/(max-min)-4)


    }
    console.log(scan)


    await fs.writeFile("networks.json", JSON.stringify(output))
}

if (import.meta.url === `file://${process.argv[1]}`) {
    const lat = parseFloat(process.argv[2].split("@")[1].split(",")[0])
    const long = parseFloat(process.argv[2].split("@")[1].split(",")[1])
    await guestimate(lat + 0.00000005, long + 0.00000005)
}
export default guestimate