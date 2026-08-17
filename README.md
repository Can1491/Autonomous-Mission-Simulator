# Autonomous Mission Simulator

C++ ile geliştirilmiş, otonom araç görev planlama ve telemetri simülasyonu.

Bu proje, bir aracın belirlenen başlangıç noktasından hedef noktaya engellerden kaçınarak otomatik rota oluşturmasını ve görev sırasında çeşitli telemetri verilerinin simüle edilmesini amaçlamaktadır.

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
- Telemetri kayıt sistemi
- Görev durumu takibi
- Görev sonunda özet rapor

## 🛰️ Görev Simülasyonu

Araç, başlangıç noktasından hedef noktasına otomatik olarak rota oluşturur.

Harita üzerinde:

- `A` → Araç / başlangıç noktası
- `G` → Hedef
- `#` → Engel
- `*` → Hesaplanan rota

Örnek:

```text
A . . . . . . . . .
* * * * * * * . . .
. . # # # . * * * .
. . . . . . . . * .
. . . . . . . . * *
. . . . . # . . . *
. . . . . # . . . *
. . . . . # . . . *
. . . . . . . . . *
. . . . . . . . . G
