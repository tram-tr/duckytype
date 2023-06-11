import requests
import json

# API URL
url = "https://baconipsum.com/api/"

def fetch_random_paragraphs(num_paragraphs):
    # Request parameters
    params = {
        "type": "all-meat",
        "paras": num_paragraphs
    }

    try:
        # Send GET request to the API
        response = requests.get(url, params=params)
        response.raise_for_status()  # Raise exception if request fails

        # Parse the response
        paragraphs = response.json()

        return paragraphs

    except requests.exceptions.RequestException as e:
        print("Failed to fetch paragraphs from the API:", str(e))
        return []

def update_paragraphs_file(paragraphs):
    try:
        # Open the paragraphs.txt file in write mode
        with open("../data/paragraphs.txt", "w") as file:
            for paragraph in paragraphs:
                file.write(paragraph + "\n\n")

        print("paragraphs.txt updated successfully.")

    except IOError as e:
        print("Failed to open paragraphs.txt for writing:", str(e))

def main():
    num_paragraphs = 10
    paragraphs = fetch_random_paragraphs(num_paragraphs)

    if paragraphs:
        update_paragraphs_file(paragraphs)
    else:
        print("Failed to fetch paragraphs from the API.")

if __name__ == "__main__":
    main()
