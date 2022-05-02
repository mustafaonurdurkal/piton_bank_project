# piton_bank_project
TCP Socket Programming
Proje Açıklaması 
  Proje bir banka yönetim sistemi uygulamasıdır. Visual Studio 2022 üzerinde  microsoft C++ derleyicisi ile yazılmış iki adet console uygulamasıdır.
  Proje birçok kullanıcının eş zamanlı olarak banka server'ına bağlanarak çesitli banka işlemlerini kolayca yapabilmesini sağlar. 
    Bu işlemler;  
                ***Kullanıcılar uygulamaya isim soyisim ve şifre ile giriş sağlayabilmektedir.
                ***Kullanıcılar bankalarındaki bakiye bilgilerini görüntülerler.<br>
                ***Kullanıcılar kendi hesaplarına para yatırabilirler.
                ***Kullanıcılar kendi hesaplarından para çekebilirler.
                ***Kullanıcılar başka hesaplara havale yada eft işlemi yapabilirler.Eft işlemi kullanıcının farklı bir bankaya transfer yapması
                       durumunda geçerlidir.Ve kendi bankasının komisyonu oranınca bakiye hesaptan düşer.Havale işlemi aynı bankaya transfer olup ücretsizdir.
                 
  
  Projede kullanılan uygulamalardan bir tanesi Server(Host) tarafını temsil ederken diğeri Client tarafını temsil eder.
  
  Bu iki uygulama birbirlerine TCP protokolünde socketler aracılığı ile bağlanır. Her iki uygulamada initializeSocket() fonksiyonunda TCP protokolünde socket ve port
  bağlantılarının oluşturulmasını görebilirsiniz.
  
  Her iki uygulama bağlandıktan sonra Server ve Client iletişimi için 2 farklı yol vardır;
      Bunlardan bir tanesi her client ve server arasındaki network için bir thread tanımlamak ve serverın her client ile ayrı ayrı ama eşzamanlı konuşabilmesini sağlar
      İkinci yol ise select() fonksiyonu aracılığı ile read/write/exception isimli 3 adet kernel dosyasi olusturup,bu dosyalarda server ve clientin socket bilgisini tutarız ve  bu dosyalara dosya tanımlayıcı değişkenlerle (fd_set) ulaşıp surekli olarak bu dosyalarda değişiklik olup olmadığını kontrol ederiz. Bir değişiklik varsa anlarız ki o clienttan bir istek gelmiş. Bu sayede server tum clientlarla ayrı ayrı konuşma yapmak yerine hepsini aynı anda dinler ve hangisi konuşuyorsa ona yanıt verir.
      İlk yol programlama tarafında programcıya avantaj sağlar çünkü tek bir konuşma fonksiyonu yazıp tüm threadlerde bu fonksiyonu çağırabiliriz.Fakat dezavantajı şudur ki: Çok sayıda thread açmak işlemciye yüklenmek demektir.Bir banka uygulamasında çok sayıda client olacağı için biz bu projede ikinci yöntem olan select() fonksiyonunu kullandık.Bu yüzden server tarafında biraz logic karmaşıklığı istemeden oluştu. (Tabi bu karmaşa düzenlenerek azaltılabilir.)
      
      
      
 
  
