
Zaimplementuj procedure, która dla danego grafu G , delta(G) >= 2, zwraca cykl
dlugosci >= delta(G) + 

1. Graf przynajmniej stopnia 
2. 

czy istnieje sasiad t' wierzcholka t, ktory nie nalezy do tymczasowej sciezki 
"pi".


biore x -> sprawdzam sasiadow -> biore t -> sprawdzam innych niz x 
-> lacze t' z t -> jak nie dodamy juz nowych w sciezce STOP


przegladam najwczesniejszy sasiad ostatniego w sciazce

x t y z x   - wypisuje do najwczesniejszego i zawracam 



zad 2 (2+3* pkt) Zaimplementuj procdure, ktore wyznacza centrum drzewa.



Algorytm Jordana (2 pkt)
	
1) jesli |v| <= 2 , zwroc srednica + 1, a centru to jeden z wierzcholkow;
	
2) w przeciwnym wypadku: niech L bedzie zbiorem wszystkich lisci w T;
	
3) szukam takich wierzcholkow ktore maja jednego sasiada (to liscie)
	
4) usuwamy liscie z T i dodajemy do srednicy 1;
	
5) powtorz dopoki nie ma 2 wierzcholkow
	
6) wtedy pkt 1).



Rozwiazanie na 5 pkt:

	
1)Przetwarzanie wstepne
 
- Licze stopnie wierzcholkow
		
- Wyznaczam ojców 
		
- odejmuje stopnie ojca i liscia i sprawdzam czy ojciec
 przypadkiem nie jest lisciem, jesli tak to do nowej listy
		  pare jego i jego ojca
		
- wszystko powtarzam

	

Sposób : 
		
- wyznaczam w jakim zakorzenic i nadaje mu pare (3,-1)
		
- patrze w 3 gdzie sa jedynki i mam pary np. (2,3) (5,3)
 i zeruje symetrycznie krawedzie
		
- potem pary z 3 i 5 np. (1,2) (4,5) (6,5)



zad 3 do wyboru zamiast 2 (5 pkt)
	
	
Zaimplementuj procedure która dla drzewa T, zwraca minimalny zbior
 dominujacy.

	
D = zbior pusty.	
	
	
Podobnie do zeszlego z wyznaczeniem ojcow i zapisujemy w 
ktorym obiegu rekurencji nastapilo wyznaczenie pary. 
	

np. (2,1,3-poziom). 
Patrzymy na liste od konca, czyli najpierw
 pary o najwyzszym pozimomie. 
nie musze pisac poziomow bo juz	sama posortowana jest tablica, tylko musze ja czytac od konca.

	
Jesli para nie nalezy do D i twoj syn nie nalezy to dodaj ojca do D. 
I powiedz dziadkowi ze jego syn nalezy.

