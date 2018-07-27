#ifndef BITSYFS_H
#define BITSYFS_H

#include <stdint.h>

#define FS_VERSION      "0.1.0"

struct mem_interface
{
    int (*read) (uint32_t addr, uint8_t *data, uint32_t nbytes);
    int (*write) (uint32_t addr, uint8_t *data, uint32_t nbytes);
    int (*erase) (uint16_t sector);
};

struct mem_config
{
    uint16_t write_size;
    uint16_t sector_size;
    uint16_t erase_state;
    uint16_t nsectors;
};

struct bfs_config
{
    uint16_t bfnode_size;
    struct mem_config mem_conf;
};

struct bfs
{
    const char magic[16] = "JWE-BITSYFS";
    const char version[8] = FS_VERSION;
    struct bfs_config bfs_conf;
};

struct bfnode
{
    uint32_t used;
    struct bfnode *first;
    struct bfnode *next;
    char name[32];
    uint32_t crc;
    uint16_t size;
    char *data;
};

/***************************** Public functions ******************************/
int bfs_init(struct mem_interface *);
int bfs_format(struct bfs_config *, bool quick);
int bfs_mount(struct bfs *);
int bfs_open(char *filename, char mode);
int bfs_read(int fd, char *data, int nbytes);
int bfs_write(int fd, char *data, int nbytes);
int bfs_seek(int fd, int offset, int whence);
void bfs_close(int fd);

#endif
