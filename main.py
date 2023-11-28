from random import randint

def read_file(file_name):
  file = open(file_name, 'r')
  content = file.read().replace('\n', ' ').split(" ")
  file.close()
  return content 

def get_keys_max_val(dict):
  keys_max_val = []
  max_value = max(dict.values())

  for key, value in dict.items():
    if value == max_value:
      keys_max_val.append(key)
      
  return keys_max_val

def isolate_words(words):
  words_isolate = []
  i = 0

  while i < len(words) and words[i] != '_':
    if i+1 < len(words) and words[i+1] == '_' :
      words_isolate.append(words[i])
    i += 1

  if i+1 < len(words) and words[i] == '_': # En caso, el guión se encuentre como primer caracter
    words_isolate.append(words[i+1])

  return words_isolate

def add_words(words, words_isolate, f_phrase):
  dict = {}

  for i in range(0, len(words)):
    # Caso en que el Guion bajo esté primero
    if f_phrase[0] == '_' and words[i] == words_isolate[0]: 
      dict[words[i-1]] = dict.get(words[i-1], 0) + 1
    # Caso en que el Guion bajo esté ultimo
    elif f_phrase[-1] == '_' and words[i] == words_isolate[0]: 
      dict[words[i+1]] = dict.get(words[i+1], 0) + 1

    # Aumenta el indice de la palabra (key del dict) que se encuentra detras el guión bajo
    elif len(words_isolate) == 2 and words[i] == words_isolate[0]:
      dict[words[i+1]] = dict.get(words[i+1], 0) + 1
    # Aumenta el indice de la palabra (key del dict) que se encuentra despues el guión bajo
    elif len(words_isolate) == 2 and words[i] == words_isolate[1]:
      dict[words[i-1]] = dict.get(words[i-1], 0) + 1

  return dict

def print_phrase(frase, dict):
  keys_max_val = get_keys_max_val(dict)
  random_word = keys_max_val[randint(0, len(keys_max_val) - 1)]
  print(' '.join(frase).replace('_', random_word))

f_lyrics = read_file('./Entradas/Fito_Paez.txt')
f_phrase = read_file('./Frases/Fito_Paez.txt')

words_isolate = isolate_words(f_phrase) # Devuelve una lista como maximo de dos elementos, contiene las words que rodean el guion bajo
dict = add_words(f_lyrics, words_isolate, f_phrase) # Agrega words que se encuentran entre los dos elementos, o el elemento, en caso de que el guion bajo se encuentre ultimo o primero
print_phrase(f_phrase, dict)