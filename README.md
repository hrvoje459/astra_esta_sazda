# astra_esta_sazda
Software implementation of AES encryption algorithm..

..in the making

TO DO:
  - <s>napravit PRAVO množenje u G. polju</s>
  - <s>ispočetka napraviti GMull</s>
  - <s>ovaj GMull možda radi, ali svejedno</s> želim pravilno implmentirati operacije u G polju
  - <s>ispočetka napraviti GMull
  - key schedule
  - addRoundKey()
  - implementirati različite duljine ključa i poruka
  - make it pretty

DO TO:
  - napravljen GMull 
      - množenje prima dva polinoma do max stupnja 15, radi ispravno ako je umnožak max stupnja 15 - dovoljno dobro
      - dijeljenje radi za sve polinome do max stupnja 15
      - funkcija gPoljePomnozi vraća umnožak polinoma modulo aes-polinom (hex = 11B)
