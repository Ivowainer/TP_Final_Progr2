from random import randint

""" 
isolate_words: List(String), Int -> List(String)
isolate_words se encarga de "aislar" las palabras en un radio n, que rodean el guion bajo para retornar una lista
que contiene a las mismas. Como maximo, pueden haber dos palabras aisaldas. 
"""
def isolate_words(phrase, radius):
  words_isolate = []
  i = 0

  while i < len(phrase) and phrase[i] != '_':
    if i+radius < len(phrase) and phrase[i+radius] == '_' :
      words_isolate.append(phrase[i])
    i += 1

  if i+radius < len(phrase) and phrase[i] == '_': # En caso, el guión se encuentre como primer caracter
    words_isolate.append(phrase[i+radius])

  return words_isolate

""" add_words: List(String), List(String), List(String) -> dict
add_words recibe como parametro la letra, la lista de las palabras aisladas que 
rodean el '_' (retorna isolate_words) y la lista que contiene las frases formateadas.
Sus varios ifs sirven para verificar casos unicos en el que el programa sufría un bug. Como
cuando el '_' es el primer elemento, o el ultimo; también cuando se necesita aumentar el radio.

Retorna un diccionario, sus claves serán las posibles palabras encontradas y sus valores sus posibilidades.
Aclaracion: En caso de estar entre dos palabras conocidas en el texto, se le suma en vez de una, dos chances, debido
a que es mas probable"""
def add_words(lyrics, words_isolate, f_phrase):
  dict = {}

  for i in range(0, len(lyrics)):
    # Caso en el que el Guion baje se encuentre entre las dos palabras coincidentes
    if len(words_isolate) == 2 and i+2 < len(lyrics)-1 and lyrics[i] == words_isolate[0] and lyrics[i+2] == words_isolate[1]:
      dict[lyrics[i+1]] = dict.get(lyrics[i+1], 0) + 100
    elif len(words_isolate) == 2 and i-2 > 0 and lyrics[i] == words_isolate[1] and lyrics[i-2] == words_isolate[0]:
      dict[lyrics[i-1]] = dict.get(lyrics[i-1], 0) + 100
      
    # Caso en que el Guion bajo esté primero
    elif f_phrase[0] == '_' and lyrics[i] == words_isolate[0]:
      dict[lyrics[i-1]] = dict.get(lyrics[i-1], 0) + 1
    # Caso en que el Guion bajo esté ultimo
    elif f_phrase[-1] == '_' and lyrics[i] == words_isolate[0]: 
      dict[lyrics[i+1]] = dict.get(lyrics[i+1], 0) + 1

    # Aumenta el indice de la palabra (key del dict) que se encuentra detras el guión bajo
    elif len(words_isolate) == 2 and lyrics[i] == words_isolate[0]: 
      dict[lyrics[i+1]] = dict.get(lyrics[i+1], 0) + 1
    # Aumenta el indice de la palabra (key del dict) que se encuentra despues el guión bajo
    elif len(words_isolate) == 2 and lyrics[i] == words_isolate[1]:
      dict[lyrics[i-1]] = dict.get(lyrics[i-1], 0) + 1

    # Caso de que se encuentre en un radio mayor.
    elif(lyrics[i] == words_isolate[0]): 
      dict[lyrics[i+1]] = dict.get(lyrics[i+1], 0) + 1
      dict[lyrics[i-1]] = dict.get(lyrics[i-1], 0) + 1
      
  return dict

""" 
get_keys_max_val: dict -> List(string)
Se le pasa a través de los parametros, el diccionario que contiene como clave las palabras mas probable
que aparezcan junto a su valor, que es su probabilidad. Buscamos retornar una lista con las CLAVES
que contienen las mayores probabilidades.
"""
def get_keys_max_val(dict):
  keys_max_val = []
  max_value = max(dict.values())

  for key, value in dict.items():
    if value == max_value:
      keys_max_val.append(key)
      
  return keys_max_val

""" 
print_phrase_in_output_file: List(String), dict, FILE -> None 
Recibe una lista de la frase sin modificar, el diccionario con la clave de las palabras mas
probables y su valor de probabilidad y el archivo de salida donde serán escrita la frase.
Crea la variable keys_max_val, que obtiene una lista con las CLAVES del diccionario con mayores valores.
Luego, obtiene una clave random de la lista keys_max_val; esto se debe a que si hay palabras que tienen
el mayor valor del diccionario, eligirá una random porque tiene la misma probabilidad de ser la que sustituya
el guion bajo.
Finalmente, sustituye el '_' con la palabra seleccionada, y la escribe en el archivo de salida
"""
def print_phrase_in_output_file(phrase, dict, file_output):
  keys_max_val = get_keys_max_val(dict)
  random_word = keys_max_val[randint(0, len(keys_max_val) - 1)] # Caso en el que las probabilidades de las palabras en el dicionario sean iguales
  final_phrase = ' '.join(phrase).replace('_', random_word)

  file_output.write(final_phrase)
  file_output.write('\n')

""" 
format_text_phrase: List(String) -> None | List(String)
format_text_phrase se encarga de formatear la frase, eliminado comas, puntos 
después e independientemente de '_'. También, convierte las mayusculas en minusculas.
"""
def format_text_phrase(phrase):
  phraseAux = ' '.join(phrase).replace("_,", "_").replace("_.", "_").replace(",", "").replace(".", "").lower().split(" ")
  return phraseAux
