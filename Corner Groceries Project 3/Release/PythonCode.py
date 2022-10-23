import re
import string


def listAllWordFreq():
    # Open the file in read mode
    text = open("CS210_Project_Three_Input_File.txt", "r")
  
    # Create an empty dictionary
    d = dict()
  
    # Loop through each line of the file
    for word in text:
        word = word.strip()
        if word in d:
            # Increment count of word by 1
            d[word] = d[word] + 1
        else:
            # Add the word to dictionary with count 1
            d[word] = 1
  
    # Print the contents of dictionary
    d = dict(sorted(d.items(), key=lambda item: item[1], reverse=True))
    for key in list(d.keys()):
        print(key, ":", d[key])

    
def getWordFreq(inputWord):
    # Open the file in read mode
    text = open("CS210_Project_Three_Input_File.txt", "r")
  
    # Create an empty dictionary
    d = dict()
  
    # Loop through each line of the file
    for word in text:
        word = word.strip()
        if word in d:
            # Increment count of word by 1
            d[word] = d[word] + 1
        else:
            # Add the word to dictionary with count 1
            d[word] = 1
  
    if inputWord in d:
        return d[inputWord]
    return -1


def saveFreqData():
    # Open the file in read mode
    text = open("CS210_Project_Three_Input_File.txt", "r")
  
    # Create an empty dictionary
    d = dict()
  
    # Loop through each line of the file
    for word in text:
        word = word.strip()
        if word in d:
            # Increment count of word by 1
            d[word] = d[word] + 1
        else:
            # Add the word to dictionary with count 1
            d[word] = 1
  
    f = open("frequency.dat", "w")
    for key in list(d.keys()):
        f.write(key + " " + str(d[key]) + "\n")
    f.close()