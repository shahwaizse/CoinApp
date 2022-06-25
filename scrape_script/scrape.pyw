import json
import requests
# Defining Binance API URL
key = "https://api.binance.com/api/v3/ticker/24hr?symbol="

currencies = ["BTCUSDT","ETHUSDT", "SOLUSDT", "LUNAUSDT","LUNCBUSD","SHIBUSDT","ADAUSDT","APEUSDT","DOGEUSDT","DOTUSDT"]

f= open ("abc.txt","w")
j = 0
for i in currencies:
    url = key+currencies[j]
    data = requests.get(url)
    data = data.json()
    j = j+1
    f.write(f"{data['symbol']} { data['weightedAvgPrice']} {data['priceChangePercent']}""\n")

f.close()