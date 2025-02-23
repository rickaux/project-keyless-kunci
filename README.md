# 🚀 Changelog Proyek RFID & Relay ESP32/Arduino  

📅 **Versi:** `v1.2.0`  
🗓 **Tanggal Rilis:** 23 Februari 2025  
📂 **Status:** Open Source  
🔎 **Lihat info detail di YouTube:** [Klik di sini](https://youtu.be/rxW7EtRJ5wc?si=GjvPGsx8PfAvg6UB)  

---

## 📷 Diagram Rangkaian  
![Project Keyless Wiring Diagram](https://raw.githubusercontent.com/rickaux/project-keyless-kunci/refs/heads/devlopment/project%20keyless%20wiring%20diagram%20fritzing_bb.jpg)  

---

## ✨ Fitur Baru  
- 🖥 **[LCD]** Integrasi **LCD 16x2 I2C** untuk menampilkan status akses.  
- 🆔 **[RFID]** Dukungan untuk **kartu RFID berbasis KTP** sebagai kartu utama.  
- 📡 **[Failover]** Implementasi **failover Starlink** untuk konektivitas yang lebih andal.  

## ⚡ Peningkatan & Optimalisasi  
- ⚙️ **[Relay]** Penggunaan **relay active low** agar lebih kompatibel dengan sistem kontrol.  
- 💾 **[Arduino]** Optimasi kode **ESP32/Arduino** untuk menghemat RAM.  
- 🔄 **[RFID]** Peningkatan **stabilitas pembacaan RFID RC522** menggunakan pin **RQ sebagai SS**.  

## 🛠 Perbaikan Bug  
- 🐛 **[BugFix]** Masalah **pembacaan kartu ganda** pada RFID telah diperbaiki.  
- 🔍 **[I2C]** **LCD I2C tidak terdeteksi** di alamat `0x2F` kini telah stabil.  
- ⏩ **[ResponseTime]** **Waktu respon relay lebih cepat** untuk menghindari delay akses.  

---

## 🚧 Kendala Saat Ini (Work In Progress)  
⚠️ **[RFID Issue]**  
> **RFID masih belum terbaca saat kartu ditempelkan**.  
> Ini menjadi tantangan terbesar saat ini. Jika Anda punya ide atau solusi, silakan kontribusi!  
> 📥 **Laporkan solusi atau saran:** [Buat Issue](https://github.com/rickaux4/repository/issues)  

---

## 📜 Catatan  
❗ **[OpenSource]** Karena ini adalah **proyek open source**, kalian **tidak boleh mengkomersialkan** kode ini!  
💙 **[Community]** Terima kasih kepada **PusatTerbuka** dan semua developer yang berkontribusi!  

---

📌 **Ingin berkontribusi?**  
🔗 [Lihat panduan kontribusi](./CONTRIBUTING.md)  
📥 **Laporkan bug atau request fitur baru:** [Buat Issue](https://github.com/rickaux4/repository/issues)  
🌟 **Dukung proyek ini dengan memberi Star!**  

---

## 🔗 Link Developer & Komunitas  
**GitHub Author:**  
- [PusatTerbuka](https://github.com/PusatTerbuka)  
- [Rickaux](https://github.com/rickaux)  

📺 **YouTube:**  
- [Pusat Terbuka](http://youtube.com/@Pusat_Terbuka)  

---

© 2025 PusatTerbuka | Dibuat dengan ❤️ oleh komunitas  
