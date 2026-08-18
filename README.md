# Autonomous Mission Simulator

C++ ile geliştirilmiş, otonom araç görev planlama, rota bulma ve telemetri simülasyonu projesidir.

Bu proje, bir otonom aracın belirlenen başlangıç konumundan hedef konumuna, harita üzerindeki engelleri dikkate alarak otomatik rota oluşturmasını ve görev sırasında araç telemetrisi üretmesini simüle eder.

---

## 🚀 Özellikler

- 10x10 görev haritası
- Başlangıç ve hedef noktası
- Engel sistemi
- Otomatik rota hesaplama
- Pathfinding algoritması
- Araç konum takibi
- Mesafe hesaplama
- Hız simülasyonu
- Batarya takibi
- Sıcaklık simülasyonu
- İvme verisi
- Gerçek zamanlı telemetri
- Telemetri geçmişi
- Telemetri dosyasına kayıt
- Görev durumu takibi
- Görev sonunda özet rapor
- Modüler C++ proje yapısı

---

## 🛰️ Görev Simülasyonu

Araç, başlangıç noktasından hedef noktasına otomatik olarak rota oluşturur.

Harita üzerinde:

- `A` → Araç / başlangıç noktası
- `G` → Hedef
- `#` → Engel
- `*` → Hesaplanan rota

Örnek:

```text
A * * * * * * * * *
. . . . . . . . . *
. . # # # . . . . *
. . . . . . . . . *
. . . . . . . . . *
. . . . . # . . . *
. . . . . # . . . *
. . . . . # . . . *
. . . . . . . . . *
. . . . . . . . . G
