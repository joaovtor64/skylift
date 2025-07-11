import fs from "fs/promises"


export default (async function (lat,long){


    await fs.writeFile("scan.json",(await (await fetch("https://api.wigle.net/api/v2/network/search?houseNumber=&road=&city=&region=&country=&postalCode=&latrange1="+lat+"&latrange2="+(lat+0.0000001)+"&longrange1="+long+"&longrange2="+(long+0.0000001)+"&variance=0.001&lastupdt=&minQoS=0&encryption=&netid=&ssid=&ssidlike=&Query=Query&lbgWdXay=561muBmIxwcDMUba9KB3", {
    "headers": {
      "accept": "application/json, text/javascript, */*; q=0.01",
      "accept-language": "en-US,en;q=0.9",
      "cache-control": "no-cache",
      "pragma": "no-cache",
      "sec-ch-ua": "\"Chromium\";v=\"137\", \"Not/A)Brand\";v=\"24\"",
      "sec-ch-ua-mobile": "?0",
      "sec-ch-ua-platform": "\"Linux\"",
      "sec-fetch-dest": "empty",
      "sec-fetch-mode": "cors",
      "sec-fetch-site": "same-site",
      "cookie": "",
      "Referer": "https://wigle.net/",
      "Referrer-Policy": "strict-origin-when-cross-origin"
    },
    "body": null,
    "method": "GET"
  })).text()))
  
  
  ;})