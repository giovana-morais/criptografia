# -*- coding: utf-8 -*-


# script que recebe um arquivo de texto e a partir dele retorna a incidência
# de cada uma das letras
import string
import sys

def char_counter(text):
    global letter_dict

    i = 0
    for i in text:
        try:
            letter_dict[i] += 1
        except KeyError:
            pass
    return text

def cypher(text):
    new = ""
    for i in text:
        new += chr(ord(i)+3)
    return new

def subs(text):
    global ordered_dict
    new_text = ""
    for i in text:
        try:
            new_text += ordered_dict[i]
        except KeyError:
            pass
    return new_text

if __name__ == '__main__':
    global letter_dict
    global ordered_dict
    letter_dict = {}

    for i in string.ascii_lowercase:
        letter_dict[i] = 0
    if sys.argv[1].endswith('.txt'):
        with open(sys.argv[1], 'rb') as file:
            text = file.read()
    else:
        text = sys.argv[1]

    lang_stats = 'a,e,o,s,r,d,n,i,t,m,u,l,c,v,p,g,q,b,f,h,j,x,z,k,y,w'.split(',')

    char_counter(text)


    print("ordem alfabética")
    for key in sorted(letter_dict.iterkeys()):
        print('{} : {}'.format(key, letter_dict[key]))

    print(type(letter_dict))
    print("maior incidência")
    ordered_list = sorted(letter_dict.iteritems(), key=lambda (k,v): (v,k), reverse=True)

    ordered_dict = {}
    i = 0
    for key, value in ordered_list:
        print('{} : {}'.format(key, letter_dict[key]))
        ordered_dict[key] = lang_stats[i]
        i += 1


    print(ordered_dict)

    new_text = subs(text)
    print("CIFRADO", text)
    print("NAO_CIFRADO", new_text)

    while True:
        inp = input('alterar dicionário?\n1-sim\t0-não ')
        if inp == 0:
            break
        lang_stats = raw_input('Digite as letras a serem trocadas separadas por ,\n').split(',')
        ordered_dict = {}
        i = 0
        for key, value in ordered_list:
            print('{} : {}'.format(key, letter_dict[key]))
            ordered_dict[key] = lang_stats[i]
            i += 1
        new_text = subs(text)
        print("CIFRADO", text)
        print("NAO_CIFRADO", new_text)
