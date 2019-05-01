Star Wars

Fatma De�irmenci  -	170201008
Berfin K�semen	  -	170201058

Bu readme.txt dosyas�, Star Wars projesine aittir.
Bu paket, kaynak kodu ile ayn� dizin i�erisinde bulunacakt�r.


1-PAKET�N ��ER���:
-------------------
StarWars.zip - Projenin kaynak kodunun ve yard�mc� dosyalar�n ziplenmi� hali.
170201008-170201058.txt - Projenin tek dosyaya indirgenmi� salt kaynak kodu.
rapor.doc - Proje raporu.
readme.txt - Bu dosya.
-------------------


2-S�STEM GEREKS�N�MLER�:
-------------------
Allegro - A game programming library - https://liballeg.org/
-------------------


3-KURULUM:
-------------------
Paket i�eri�ini, yukar�da g�rebilirsiniz.

Bu kod, iki adet Windows kurulu makinede �al��t�r�ld�.

Bu iki durumda da, kod, herhangi bir hata vermeksizin, daha �nceden
belirlenen kriterlere uygun �al��t�.

-------------------


4- PARAMETRELER
-------------------
Kodun �al��mas� i�in allegro k�t�phanesi kurulmal� ve Harita.txt StarWars
klas�r�nde olmal�. 
------------------


5- PROGRAMIN KULLANIMI
-----------------------------
Star Wars Projesi, Harita.txt dosyas� i�indeki bilgileri okur ve okunan bilgilere
g�re k�t� karakterleri, iyi karakteri ve map'i olu�turur. Kullan�c�n�n hareketine g�re
iyi karakteri hareket ettirir ve en k�sa yol bulma algoritmas� yard�m� ile de
k�t� karakterler kullan�c�ya ilerler. 

Program ilk �al��t�r�ld���nda allegro k�t�phanesi etkinle�tirilir ve Harita.txt okunur. 
Ard�ndan aray�z a��l�r ve okunan bilgiler burada �izilir. Kullan�c�n�n klavye ile(y�n oklar�)
hareketi sonucu her k�t� karakter i�in en k�sa yol hesaplan�r.

Hesaplanan bu en k�t� yol yine allegro k�t�phanesi yard�m� ile ekrana �izilir. 

�yi karakter, k�t� karaktere yakalan�rsa karakterin t�r�ne �zel olarak can d���m� yap�l�r.
Ard�ndan t�m karakterler ba�lang�� konumuna d�ner.

MasterYoda iyi karakterinin can� yar�m yar�m azal�rken, LukeSkywalker iyi karakterinin
can� birer birer azal�r.

Ayn� zamanda DarthVader k�t� karakteri duvarlardan ge�ebilir, KyloRen 2�er birim ilerler.
Stormtrooper bir birim ilerler ve duvarlardan ge�emez, ek bir �zelli�i yoktur.

Kullan�c�n�n can� kalmazsa oyunu kaybetti�inden display kapan�r, can� bitmeden ��k�� 
noktas�na ula��rsa da oyunu kazan�r ve display kapan�r. 

B�ylece program sonland�r�lm�� olur.
