# 🚀 Minitalk

**Minitalk**, Unix sinyalleri kullanarak iki süreç arasında iletişim kuran bir 42 School projesidir. Bu proje, `SIGUSR1` ve `SIGUSR2` sinyalleri ile bit manipülasyonu kullanarak client'tan server'a mesaj gönderimi sağlar.

---

## 📋 İçindekiler

- [Proje Hakkında](#-proje-hakkında)
- [Özellikler](#-özellikler)
- [Kurulum](#-kurulum)
- [Kullanım](#-kullanım)
- [Nasıl Çalışır?](#-nasıl-çalışır)
- [Bonus Özellikleri](#-bonus-özellikleri)
- [Teknik Detaylar](#-teknik-detaylar)
- [Örnekler](#-örnekler)

---

## 🎯 Proje Hakkında

Minitalk projesi, inter-process communication (IPC) kavramını Unix sinyalleri kullanarak öğrenmeyi amaçlar. Server ve client olmak üzere iki program içerir:

- **Server**: Başlatıldığında PID'sini gösterir ve sinyalleri dinler
- **Client**: Server'ın PID'sini ve göndermek istediği mesajı parametre olarak alır

---

## ✨ Özellikler

### Temel Özellikler
- ✅ Unix sinyalleri ile haberleşme (SIGUSR1 & SIGUSR2)
- ✅ ASCII karakterlerinin bit seviyesinde iletimi
- ✅ Çoklu client desteği
- ✅ Hata yönetimi ve geçerlilik kontrolleri
- ✅ 42 Norm standartlarına uygunluk

### Bonus Özellikler
- ✅ Server'dan client'a acknowledgment (onay) gönderimi
- ✅ Mesaj başarıyla alındığında bildirim
- ✅ Unicode karakterleri desteği (UTF-8)
- ✅ Gelişmiş hata mesajları ve renkli çıktılar

---

## 🔧 Kurulum

### Gereksinimler
- GCC derleyici
- Make
- Unix/Linux işletim sistemi

### Derleme

```bash
# Temel versiyonu derlemek için
make

# Bonus versiyonunu derlemek için
make bonus

# Temizlik işlemleri
make clean      # Object dosyalarını siler
make fclean     # Tüm derlenmiş dosyaları siler
make re         # Yeniden derleme (fclean + all)
```

Derleme sonrası oluşan dosyalar:
- `server` ve `client` (temel versiyon)
- `server_bonus` ve `client_bonus` (bonus versiyon)

---

## 📖 Kullanım

### 1. Server'ı Başlatma

```bash
# Temel versiyon
./server

# Bonus versiyon
./server_bonus
```

Server başladığında PID'ini gösterecektir:
```
Server PID: 12345
```

### 2. Client ile Mesaj Gönderme

Yeni bir terminal açın ve:

```bash
# Temel versiyon
./client [SERVER_PID] "Mesajınız"

# Bonus versiyon
./client_bonus [SERVER_PID] "Mesajınız"
```

#### Örnek Kullanım:

```bash
# Terminal 1 - Server'ı başlat
./server_bonus
# Çıktı: Server PID: 12345

# Terminal 2 - Client'tan mesaj gönder
./client_bonus 12345 "Merhaba Dünya!"
# Çıktı: Message received successfully.
```

---

## 🔍 Nasıl Çalışır?

### Bit Kodlama Mekanizması

1. **Client Tarafı:**
   - Her karakter 8 bite dönüştürülür
   - Her bit için bir sinyal gönderilir:
     - `SIGUSR1` → Bit 0
     - `SIGUSR2` → Bit 1
   - Mesaj bitince NULL terminator (8 adet 0 bit) gönderilir

2. **Server Tarafı:**
   - Gelen sinyalleri dinler
   - Her sinyali bir bit olarak yorumlar
   - 8 bit toplandığında karakteri oluşturur ve yazdırır
   - Bonus versiyonda her bit alındıktan sonra ACK gönderir

### Sinyal Akışı

```
CLIENT                          SERVER
   |                               |
   |---[SIGUSR2 (bit=1)]--------->|
   |<--[SIGUSR1 (ACK)]------------|
   |---[SIGUSR1 (bit=0)]--------->|
   |<--[SIGUSR1 (ACK)]------------|
   |          ...                 |
   |---[8 bits = 1 char]--------->|
   |                          [Print char]
   |<--[SIGUSR2 (Complete)]-------|
```

---

## 🎁 Bonus Özellikleri

Bonus versiyon şu ek özellikleri içerir:

### 1. Acknowledgment (Onay) Sistemi
- Server her bit aldığında client'a SIGUSR1 sinyali gönderir
- Bu, mesajın senkronize şekilde iletilmesini sağlar

### 2. Başarı Bildirimi
- Mesaj tamamlandığında server, client'a SIGUSR2 gönderir
- Client ekrana başarı mesajı yazdırır:
```
Message received successfully.
```

### 3. Unicode Desteği
- Bonus versiyonda 127'den büyük ASCII değerleri desteklenir
- Türkçe karakterler (ğ, ü, ş, ı, ö, ç) gönderilebilir

### 4. Gelişmiş Hata Mesajları
- Renkli terminal çıktıları
- Daha detaylı hata açıklamaları

---

## 🛠 Teknik Detaylar

### Kullanılan Fonksiyonlar

#### Signal İşleme
- `signal()` - Sinyal yöneticisi kaydetme
- `sigaction()` - Gelişmiş sinyal yönetimi (SA_SIGINFO ile)
- `kill()` - Sürece sinyal gönderme
- `pause()` - Sinyal bekleme

#### Sistem Fonksiyonları
- `getpid()` - Süreç ID'si alma
- `sigemptyset()` - Sinyal maskesi temizleme

### PID Validasyonu

```c
// PID kontrolleri
- PID <= 0         → Geçersiz
- PID >= 4194304   → Geçersiz (Linux max PID)
- PID uzunluğu > 8 → Geçersiz
```

### Bit Manipülasyonu

```c
// Bit çıkarma (Client)
int bit = (character >> bit_position) & 1;

// Bit birleştirme (Server)
character |= (signal == SIGUSR2) << bit_position;
```

---

## 💡 Örnekler

### Örnek 1: Basit Mesaj

```bash
./server_bonus
# Server PID: 54321

# Başka terminal
./client_bonus 54321 "Hello"
```

**Server çıktısı:**
```
Server PID: 54321
Hello
```

**Client çıktısı:**
```
Message received successfully.
```

### Örnek 2: Uzun Mesaj

```bash
./client_bonus 54321 "Bu çok uzun bir mesajdır ve tüm karakterler başarıyla iletilecektir!"
```

### Örnek 3: Özel Karakterler (Bonus)

```bash
./client_bonus 54321 "Merhaba! 42İstanbul 🚀"
./client_bonus 54321 "Türkçe karakterler: ğüşıöç"
```

### Örnek 4: Hatalı Kullanım

```bash
# Yanlış PID
./client 999999999 "test"
# Çıktı: Error: Invalid PID

# Eksik parametre
./client 12345
# Çıktı: Error: Invalid Argument Or PID
#        USED: ./client <server_pid> <string>
```

---

## 🐛 Hata Ayıklama

### Sık Karşılaşılan Hatalar

1. **"Error: Invalid PID"**
   - Çözüm: Doğru server PID'ini kullandığınızdan emin olun
   - Server'ın çalıştığını kontrol edin

2. **"Error: enter correct pid"**
   - Çözüm: Server sürecinin hala aktif olduğunu doğrulayın
   - `ps aux | grep server` komutu ile kontrol edin

3. **"Signal Error"**
   - Çözüm: Sistem sinyal yönetiminde sorun var
   - Süreç haklarını kontrol edin

### Debug Modu

Test için `SIGUSR1` ve `SIGUSR2` sinyallerini manuel gönderebilirsiniz:

```bash
# Server PID'si 12345 olsun
kill -SIGUSR1 12345  # Bit 0 gönder
kill -SIGUSR2 12345  # Bit 1 gönder
```

---

## 📊 Proje Yapısı

```
minitalk/
├── Makefile              # Derleme kuralları
├── README.md            # Bu dosya
├── minitalk.h           # Temel header
├── minitalk_bonus.h     # Bonus header
├── server.c             # Server programı
├── server_bonus.c       # Bonus server
├── client.c             # Client programı
├── client_bonus.c       # Bonus client
└── libft/               # Yardımcı kütüphane
    ├── libft.h
    ├── ft_*.c           # Libft fonksiyonları
    └── ft_printf/       # Printf implementasyonu
        ├── ft_printf.h
        └── ft_*.c
```

---

## 📚 Öğrenilen Kavramlar

- ✅ Unix sinyalleri ve inter-process communication
- ✅ Bit manipülasyonu ve binary işlemler
- ✅ Asenkron programlama
- ✅ Signal handling (sigaction)
- ✅ Process management
- ✅ Error handling ve validation
- ✅ Makefile kullanımı

---

## 🤝 Katkıda Bulunma

Bu proje 42 School müfredatının bir parçasıdır. Eğitim amaçlıdır.

---

## 📝 Notlar

- Server aynı anda birden fazla client'tan mesaj alabilir
- Uzun mesajlar için biraz zaman alabilir (her karakter = 8 sinyal)
- Ctrl+C ile server'ı durdurabilirsiniz
- Bonus versiyonu daha güvenilir ve hızlıdır (acknowledgment sistemi sayesinde)

---

## 👨‍💻 Geliştirici

**malbayra** - 42 İstanbul

---

## 📄 Lisans

Bu proje 42 School projesidir ve eğitim amaçlıdır.

---

## 🔗 Yararlı Kaynakler

- [Signal Man Page](https://man7.org/linux/man-pages/man7/signal.7.html)
- [Sigaction Documentation](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [42 School](https://www.42istanbul.com.tr/)

---

**⭐ Projeyi beğendiyseniz yıldız vermeyi unutmayın!**
