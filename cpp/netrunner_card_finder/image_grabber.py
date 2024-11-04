#!/usr/bin/python3
"""
    - Downloads card images from NetrunnerDB API at endpoint:
            /api/v3/public/cards
        -- images downloaded to: ./images/
    - Downloads json data from above endpoint, if necessary
        -- json downloaded to: ./cards.json
    How to use this file effectively:
        chmod -v 744 image_grabber.py
        ./image_grabber.py > image_log.txt 2>&1
"""
from pathlib import Path
from socket import setdefaulttimeout
from urllib.request import urlopen, urlretrieve
import json


def card_image_grabber():
    Path("./images").mkdir(parents=True, exist_ok=True)
    with open("./cards.json") as cards:
        card_data = json.load(cards)
        print("[*] Card data loaded")
        print("[*] Downloading card images")
        for index, obj in enumerate(card_data['data']):
            """
                Uncomment below if process failed to complete for any reason
                and last completed index is known
            """
            # if idx < 1248:
            #     continue
            printing_ids = obj['attributes']['printing_ids']
            for card in printing_ids:
                print(f"{index:04} : {card} : {obj['attributes']['title']}")
                urlretrieve(
                    f"https://card-images.netrunnerdb.com/v2/large/{card}.jpg",
                    f"./images/{card}.jpg"
                )


def cards_json_grabber():
    api_url, endpoint, params = \
        "https://api-preview.netrunnerdb.com", \
        "/api/v3/public/cards", \
        "?page[limit]=9999"
    print(f"[*] Downloading card data from {api_url}{endpoint}")
    card_request = urlopen(f"{api_url}{endpoint}{params}")
    card_data = json.load(card_request)
    with open("./cards.json", 'w') as card_file:
        json.dump(card_data, card_file)


if __name__ == "__main__":
    setdefaulttimeout(60)
    cards_json = Path("./cards.json")
    if not cards_json.is_file():
        print("[*] Card data not found")
        cards_json_grabber()
    card_image_grabber()
