# piton_bank_project
TCP Socket Programming<br/>
Proje Açıklaması <br/>
  Proje bir banka yönetim sistemi uygulamasıdır. Visual Studio 2022 üzerinde  microsoft C++ derleyicisi ile yazılmış iki adet console uygulamasıdır.
  Proje birçok kullanıcının eş zamanlı olarak banka server'ına bağlanarak çesitli banka işlemlerini kolayca yapabilmesini sağlar. 
    Bu işlemler;<br/><br/>
             ![githubresim](https://user-images.githubusercontent.com/32611163/166250281-3dc2375b-8eec-4462-83db-14b043ed873e.png)

  
  Projede kullanılan uygulamalardan bir tanesi Server(Host) tarafını temsil ederken diğeri Client tarafını temsil eder.
  
  Bu iki uygulama birbirlerine TCP protokolünde socketler aracılığı ile bağlanır. Her iki uygulamada initializeSocket() fonksiyonunda TCP protokolünde socket ve port
  bağlantılarının oluşturulmasını görebilirsiniz.
  
  Her iki uygulama bağlandıktan sonra Server ve Client iletişimi için 2 farklı yol vardır;
      Bunlardan bir tanesi her client ve server arasındaki network için bir thread tanımlamak ve serverın her client ile ayrı ayrı ama eşzamanlı konuşabilmesini sağlar<br/><br/>
      İkinci yol ise select() fonksiyonu aracılığı ile read/write/exception isimli 3 adet kernel dosyasi olusturup,bu dosyalarda server ve clientin socket bilgisini tutarız ve  bu dosyalara dosya tanımlayıcı değişkenlerle (fd_set) ulaşıp surekli olarak bu dosyalarda değişiklik olup olmadığını kontrol ederiz. Bir değişiklik varsa anlarız ki o clienttan bir istek gelmiş. Bu sayede server tum clientlarla ayrı ayrı konuşma yapmak yerine hepsini aynı anda dinler ve hangisi konuşuyorsa ona yanıt verir.<br/><br/>
      İlk yol programlama tarafında programcıya avantaj sağlar çünkü tek bir konuşma fonksiyonu yazıp tüm threadlerde bu fonksiyonu çağırabiliriz.Fakat dezavantajı şudur ki: Çok sayıda thread açmak işlemciye yüklenmek demektir.Bir banka uygulamasında çok sayıda client olacağı için biz bu projede ikinci yöntem olan select() fonksiyonunu kullandık.Bu yüzden server tarafında biraz logic karmaşıklığı istemeden oluştu. (Tabi bu karmaşa düzenlenerek azaltılabilir.)<br/><br/>
      
      Bu baglantılar düzgün bir şekilde sağlandıktan sonra receive ve send fonksiyonları ile server ve client arası senkronizasyon logic kontrolleri ile sağlanıyor.Gerekli exception hata kontrolleri yapılıyor.Veriler server tarafında 3 adet txt dosyası tarafından tutuluyor.Bu dosyalar card.txt bankçtxt ve customer.txt
Yapılan testlerde uygulama sorunsuz bir şekilde çalışıyor.
      

 
  
