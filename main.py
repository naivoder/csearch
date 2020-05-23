import csearch
import os

if __name__=="__main__":
    target = input("Which directory would you like to search? ")
    phrase = input("What string are you looking for? ").encode()
    file_list = []
    for root, dirs, files in os.walk(target):
        for name in files:
            file_list.append(os.path.join(root, name))
    while file_list:
        check_file = file_list.pop().encode()
        csearch._find(check_file, phrase)
