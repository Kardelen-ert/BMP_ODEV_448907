Bu çalışmada C++ programlama dili kullanarak BMP formatındaki bir görüntü dosyası üzerinde temel bir görüntü işleme programı yaptım. Programda ilk olarak BMP dosyasını binary modda açtım ve dosyanın ilk 54 byte’lık header kısmını okudum. Header üzerinden görüntünün genişlik, yükseklik ve bit derinliği (bpp) bilgilerini çıkardım. Dosyanın gerçekten bir BMP dosyası olup olmadığını kontrol ettim ve sadece 24-bit ile 32-bit BMP dosyalarını destekleyecek şekilde kısıtlama koydum.

Görüntü bilgilerini aldıktan sonra piksel başına düşen byte sayısını hesapladım. BMP dosyalarında her satırın 4 byte hizalamaya sahip olmasından dolayı satır uzunluğunu (rowSize) padding’i de dikkate alarak hesapladım. Daha sonra tüm piksel verisini tutabilmek için dinamik bellek ayırdım ve dosyadan okuduğum piksel verilerini bu alana aktardım.

Görüntü işleme kısmında, görüntünün merkez noktasını hesapladım ve bu merkezin etrafında verilen boyutta kare bir alan belirledim. Belirlediğim bu alan içerisindeki piksellerin mavi, yeşil ve kırmızı (BGR) değerlerini sıfırlayarak orta kısımda siyah bir kare oluşturdum. Eğer görüntü 32-bit ise alfa kanalını da uygun şekilde ayarladım. Bu işlemleri yaparken her piksel için doğru indeksi hesaplayarak doğrudan piksel dizisi üzerinde işlem yaptım.

Görüntü üzerindeki işlemleri tamamladıktan sonra, orijinal BMP header bilgilerini ve değiştirilmiş piksel verilerini kullanarak yeni bir BMP dosyası oluşturdum ve sonucu output.bmp adıyla kaydettim. Programın sonunda dinamik olarak ayırdığım belleği serbest bırakarak bellek sızıntısı oluşmasını engelledim.

Sonuç olarak bu ödevde, BMP dosya yapısını daha iyi anlamış oldum ve C++ dilinde dosya okuma-yazma, dinamik bellek kullanımı ve piksel tabanlı görüntü işleme konularında pratik yaptım. 
