from utils.helpers import *
from random import randint
from sys import argv

""" Se encarga de obtener el archivo que contiene las frases del artista
para luego iterar en cada salto de linea: 
  - guardar su contenido en forma de lista (word_line_aux)
  - eliminar las comillas simples '' que quedan de sobra en word_line_aux
  - guarda word_line_aux en content
por ultimo, reotrna content, que es una lista que contiene listas de cada palabra contenida en linea
del archivo frase """
def read_file(file_name):
  file = open(file_name, 'r')
  lines_of_text = file.readlines()

  content = []

  for line_of_text in lines_of_text:
    word_line_aux = line_of_text.replace('\n', '').split(' ')

    # Eliminar '' de la lista
    if '' in word_line_aux:
      word_line_aux.remove('')

    content.append(word_line_aux) # Guarda ['Te', '_,', 'unos', 'chinos', 'en', 'madrid'] dentro de la lista

  file.close()

  return content 

def main(name):
  f_lyrics = open("./Entradas/" + name + ".txt")
  lyrics = f_lyrics.read().replace('\n', ' ').split(' ')  # La lista contiene como elementos cada palabra del archivo
  f_lyrics.close()

  f_phrase = read_file('./Frases/' + name + '.txt') 

  file_output = open("./Salidas/" + name + ".txt", 'w+')

  """ Iteración por cada frase en lista de frases """
  for phrase in f_phrase:
    phraseAux = format_text_phrase(phrase) # Utilizo un auxiliar formateado para mantener las frases originales de f_phrase
    
    if '_' in phraseAux:
      words_isolate = isolate_words(phraseAux, 1) # Devuelve una lista como maximo de dos elementos, que contiene las words que rodean el guion bajo

      dict = add_words(lyrics, words_isolate, phraseAux) # Agrega palabras que se encuentran entre los dos elementos, o el elemento, en caso de que el guion bajo se encuentre ultimo o primero

      # Caso de que las palabras que rodean el guion bajo, no existan, aumenta el radio
      i = 2
      while i < len(phrase)+1 and len(dict) == 0:
        try:
          dict = add_words(lyrics, isolate_words(phraseAux, i), phraseAux)
          i+=1
        except:
          dict[lyrics[randint(0, len(lyrics))]] = 1
          
    print_phrase_in_output_file(phrase, dict, file_output)

  file_output.close()

""" ARGUMENTS """
script, name = argv
main(name)