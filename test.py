f_letra = open('./Entradas/Fito_Paez.txt', 'r')
f_frase = open('./Frases/Fito_Paez.txt', 'r')

""" === AISLAR UNICAMENTE PALABRAS RODEADAS POR EL GUION "_" === """
f_frase_frase = f_frase.read()
frase = f_frase_frase.split(" ")
palabras_frases = []
i = 0;

while i<len(frase) and frase[i] != '_':
        
    if  i+1<len(frase) and frase[i+1] == '_':
        palabras_frases.append(frase[i])

    i+=1;

if i+1<len(frase) and frase[i] == '_' :
    palabras_frases.append(frase[i+1])

""" === AGREGAR PALABRAS ANTES Y DESPUES DE palabras_frases === """
palabras_texto = f_letra.read().replace('\n', ' ').split(" ")
dic = {}

""" TODO: 
    - En caso sea una unica palabra ['']
    - En caso las palabras que rodean el guion no estén en Fito_Paez.txt
    - MODULARIZAR Y FUNCIONES, EVITAR GLOBALS """
    
for i in range(0, len(palabras_texto)):
    if(palabras_texto[i] == palabras_frases[0] and palabras_texto[i+1] in dic):
        dic[palabras_texto[i+1]] += 1
    elif(palabras_texto[i] == palabras_frases[0]):
        dic[palabras_texto[i+1]] = 1

    if(palabras_texto[i] == palabras_frases[1] and palabras_texto[i-1] in dic):
        dic[palabras_texto[i-1]] += 1
    elif(palabras_texto[i] == palabras_frases[1]):
        dic[palabras_texto[i-1]] = 1

max_key = max(dic, key=dic.get)

print(f_frase_frase.replace('_', max_key))


f_letra.close()
f_frase.close()