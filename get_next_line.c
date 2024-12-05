/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husarpka <husarpka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:19:42 by husarpka          #+#    #+#             */
/*   Updated: 2024/12/02 16:47:17 by husarpka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>





// BUFFER_SIZE değerini tanımlayın
#define BUFFER_SIZE 5

// ft_strdup fonksiyonu


// Dosya tanımlayıcısından veri okuma ve tamponu güncelleme
static int read_from_fd(int fd, char **buffer) {
    char temp[BUFFER_SIZE + 1];
    int bytes_read = read(fd, temp, BUFFER_SIZE);
    if (bytes_read > 0) {
        temp[bytes_read] = '\0';
        *buffer = ft_strjoin(*buffer, temp);
    }
    return bytes_read;
}

// Tampon içinden bir satır alma ve tamponu güncelleme
static char *get_line_from_buffer(char **buffer) {
    int i = 0;
    char *line = NULL;
    char *new_buffer;

    // Tampon içinde bir yeni satır karakteri arama
    while (*buffer && (*buffer)[i] && (*buffer)[i] != '\n') {
        i++;
    }

    // Eğer yeni satır karakteri bulunursa
    if ((*buffer)[i] == '\n') {
        (*buffer)[i] = '\0'; // Satır sonunu null terminator ile değiştir
        line = ft_strdup(*buffer); // Satırı al
        new_buffer = ft_strdup(&(*buffer)[i + 1]); // Tamponu güncelle
        free(*buffer); // Eski tamponu serbest bırak
        *buffer = new_buffer; // Yeni tamponu atayın
    } else if (*buffer && (*buffer)[0]) { // Eğer tamponda veri varsa ve yeni satır yoksa
        line = ft_strdup(*buffer);
        free(*buffer); // Belleği serbest bırak
        *buffer = NULL; // Tamponu sıfırla
    }

    return line;
}

// Ana fonksiyon: Satırı döndürmek için
char *ft_get_next_line(int fd) {
    static char *buffer = NULL; // Statik tampon
    int bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0) {
        return NULL;
    }

    // İlk okuma işlemi
    bytes_read = read_from_fd(fd, &buffer);

    // Okunan bayt sayısı pozitif olduğu sürece devam et
    while (bytes_read > 0) {
        // Satırın tamamı tamponda varsa, satırı döndür
        char *line = get_line_from_buffer(&buffer);
        if (line) {
            return line; // Satırı döndür
        }
        // Yeni verileri oku
        bytes_read = read_from_fd(fd, &buffer); 
    }

    // Eğer tamponda kalan veri varsa, onu döndür
    if (bytes_read == 0 && buffer && buffer[0]) {
        return get_line_from_buffer(&buffer); // Kalan veriyi döndür
    }

    free(buffer);
    buffer = NULL; // Belleği temizle
    return NULL; // Hiçbir şey yoksa NULL döndür
}

int main() {
    int fd = open("test.txt", O_RDONLY | O_CREAT, 0644); // Dosyayı aç veya oluştur
    if (fd < 0) {
        perror("Dosya açılamadı");
        return 1; // Hata durumunda çıkış
    }

    char *line;

    // Satır okuma döngüsü
    while ((line = ft_get_next_line(fd)) != NULL) {
        printf("%s\n", line); // Okunan satırı yazdır
        free(line); // Belleği serbest bırak
    }

    close(fd); // Dosyayı kapat
    return 0; // Başarıyla çıkış
}
