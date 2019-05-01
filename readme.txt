Star Wars

Fatma Deðirmenci  -	170201008
Berfin Kösemen	  -	170201058

Bu readme.txt dosyasý, Star Wars projesine aittir.
Bu paket, kaynak kodu ile ayný dizin içerisinde bulunacaktýr.


1-PAKETÝN ÝÇERÝÐÝ:
-------------------
StarWars.zip - Projenin kaynak kodunun ve yardýmcý dosyalarýn ziplenmiþ hali.
170201008-170201058.txt - Projenin tek dosyaya indirgenmiþ salt kaynak kodu.
rapor.doc - Proje raporu.
readme.txt - Bu dosya.
-------------------


2-SÝSTEM GEREKSÝNÝMLERÝ:
-------------------
Allegro - A game programming library - https://liballeg.org/
-------------------


3-KURULUM:
-------------------
Paket içeriðini, yukarýda görebilirsiniz.

Bu kod, iki adet Windows kurulu makinede çalýþtýrýldý.

Bu iki durumda da, kod, herhangi bir hata vermeksizin, daha önceden
belirlenen kriterlere uygun çalýþtý.

-------------------


4- PARAMETRELER
-------------------
Kodun çalýþmasý için allegro kütüphanesi kurulmalý ve Harita.txt StarWars
klasöründe olmalý. 
------------------


5- PROGRAMIN KULLANIMI
-----------------------------
Star Wars Projesi, Harita.txt dosyasý içindeki bilgileri okur ve okunan bilgilere
göre kötü karakterleri, iyi karakteri ve map'i oluþturur. Kullanýcýnýn hareketine göre
iyi karakteri hareket ettirir ve en kýsa yol bulma algoritmasý yardýmý ile de
kötü karakterler kullanýcýya ilerler. 

Program ilk çalýþtýrýldýðýnda allegro kütüphanesi etkinleþtirilir ve Harita.txt okunur. 
Ardýndan arayüz açýlýr ve okunan bilgiler burada çizilir. Kullanýcýnýn klavye ile(yön oklarý)
hareketi sonucu her kötü karakter için en kýsa yol hesaplanýr.

Hesaplanan bu en kötü yol yine allegro kütüphanesi yardýmý ile ekrana çizilir. 

Ýyi karakter, kötü karaktere yakalanýrsa karakterin türüne özel olarak can düþümü yapýlýr.
Ardýndan tüm karakterler baþlangýç konumuna döner.

MasterYoda iyi karakterinin caný yarým yarým azalýrken, LukeSkywalker iyi karakterinin
caný birer birer azalýr.

Ayný zamanda DarthVader kötü karakteri duvarlardan geçebilir, KyloRen 2þer birim ilerler.
Stormtrooper bir birim ilerler ve duvarlardan geçemez, ek bir özelliði yoktur.

Kullanýcýnýn caný kalmazsa oyunu kaybettiðinden display kapanýr, caný bitmeden çýkýþ 
noktasýna ulaþýrsa da oyunu kazanýr ve display kapanýr. 

Böylece program sonlandýrýlmýþ olur.
