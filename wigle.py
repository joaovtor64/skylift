import requests
from requests.auth import HTTPBasicAuth
import pandas as pd
from pandas import json_normalize
import folium
import geopandas

# SETTING WiGLE USERNAME & PASSWORD FOR API CALL:
wigle_username = ''
wigle_password = ''

city = 'Sao Paulo'
# SETTING PARAMETERS:
payload = {'first': '1', 'freenet': 'false', 'paynet': 'false', 'addresscode': city, 'api_key': (wigle_username + wigle_password).encode()}
# FETCHING JSON RESPONSE FROM WiGLE:
details = requests.get(url='https://api.wigle.net/api/v2/network/geocode', params=payload, auth=HTTPBasicAuth(wigle_username, wigle_password)).json()

# SETTING PARAMETERS:
payload = {'latrange1':'-23.7106507', 'latrange2':'-23.3906507', 'longrange1':'-46.7933824', 'longrange2':'-46.4733824', 'api_key': (wigle_username + wigle_password).encode()}
# FETCHING JSON RESPONSE FROM WiGLE:
results = requests.get(url='https://api.wigle.net/api/v2/network/search', params=payload, auth=HTTPBasicAuth(wigle_username, wigle_password)).json()

# EXTRACTING 'RESULTS' AS A PANDAS DATAFRAME TO WORK WITH:
df = json_normalize(results['results'])
# RENAMING COLUMNS FOR GEOPLOTLIB:
df = df.rename(columns={'trilat': 'lat', 'trilong': 'lon'})
cols = list(df.columns)
# PREVIEWING AVAILABLE INFORMATION:
print(f"Result obtained has {df.shape[0]} rows and {df.shape[1]} columns in it. \n\nThe list of columns include {cols}")

gdf = geopandas.GeoDataFrame(
    df, geometry=geopandas.points_from_xy(df.lon, df.lat), crs="EPSG:4326"
)

interactive_map1 = folium.Map(
    location=(-23.568399795078903, -46.6474148638533),
    zoom_start=10
)

addresses_layer = folium.features.GeoJson(gdf)
addresses_layer.add_to(interactive_map1)
interactive_map1