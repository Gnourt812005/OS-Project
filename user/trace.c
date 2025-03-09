#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Chương trình trace: dùng để bật chế độ theo dõi system call và chạy một chương trình khác.
int
main(int argc, char *argv[])
{
    int mask;

    // Kiểm tra số lượng đối số: cần ít nhất 3 đối số (tên chương trình, mask, chương trình cần chạy)
    if(argc < 3){
        fprintf(2, "Usage: trace <mask> <program> [args...]\n");
        exit(1);
    }

    // Chuyển đổi đối số mask (argv[1]) từ chuỗi sang số nguyên
    mask = atoi(argv[1]);

    // Gọi system call trace với mask đã nhận.
    // Hệ thống kernel sẽ lưu mask này trong trường của tiến trình hiện tại,
    // và các system call được gọi bởi tiến trình này (và con cháu của nó) sẽ được in ra nếu thuộc mask.
    if(trace(mask) < 0){
        fprintf(2, "trace failed\n");
        exit(1);
    }

    // Chạy chương trình được chỉ định bởi các đối số sau mask.
    // exec sẽ thay thế tiến trình hiện tại bằng chương trình mới.
    exec(argv[2], &argv[2]);
    
    // Nếu exec trả về, tức là có lỗi xảy ra.
    fprintf(2, "exec %s failed\n", argv[2]);
    exit(1);
}
