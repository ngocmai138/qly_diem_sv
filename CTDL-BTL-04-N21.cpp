#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

/*

+ Thong tin can quan ly gom: SinhVien, MonHoc, Diem, BangDiem
- SinhVien gom: ma sinh vien, ho ten
- MonHoc gom: ma mon hoc, ten mon hoc, diem trung binh , tong diem mon, so sinh vien
- Diem gom: ma sinh vien, ma mon hoc, diem
- BangDiem gom:  ma sinh vien, danh sach Diem, so mon hoc, diem trung binh, tong diem

+Chuong trinh thuc hien cac yeu cau sau:
- Nhap va in Sinh Vien
- Ghi va doc vao file Sinh Vien
- Nhap va in Mon Hoc
- Ghi va doc vao file Mon Hoc
- Nhap va in Bang Diem
- Ghi va doc vao file Bang Diem

- Them Bang diem
- Sua Bang diem
- Xoa Bang diem

- Tim kiem Bang diem theo ten sinh vien
- Tim kiem Bang diem theo ma sinh vien

- Sap xep danh sach sinh vien co diem trung binh tu thap den  cao
- Sap xep danh sach sinh vien co diem trung binh tu cao den thap
- Sap xep danh sach mon hoc co diem trung binh tu thap den cao
- Sap xep danh sach mon hoc co diem trung binh tu cao den thap

- Tim sinh vien co diem trung binh lon nhat
- Tim sinh vien co diem trung binh nho nhat
- Tim mon hoc co diem trung binh cao nhat
- Tim mon hoc co diem trung binh thap nhat

- Tinh tong diem cua tung mon hoc
- Tinh tong diem cua tung sinh vien
- Tinh diem trung binh cua tung sinh vien
- Tinh diem trung binh cua tat ca sinh vien
- Dem tong so sinh vien

- Thong ke danh sach sinh vien co diem trung binh lon hon so nhap vao
- Thong ke danh sach mon hoc co diem trung binh lon hon so nhap vao
- Thong ke danh sach sinh vien co diem lon hon 8 cua ma mon hoc nhap vao
- Thong ke danh sach mon hoc khong co sinh vien duoi 5 diem
- Thong ke danh sach sinh vien co diem mon bat ky duoi 5
*/

/* Khai bao cau truc dang DSLK don de chua danh sach SinhVien */
struct SinhVien
{
    int maSV;
    char tenSV[30];
};
struct NodeSV
{
    SinhVien info;
    struct NodeSV *next;
};
struct ListSV
{
    NodeSV *Head;
    NodeSV *Tail;
};

/* Khai bao cau truc dang DSLK don de chua danh sach MonHoc */
struct MonHoc
{
    int maMonHoc, ssv;
    char tenMonHoc[20];
    float diemTB, tongDiem;
};
struct NodeMH
{
    MonHoc info;
    struct NodeMH *next;
};
struct ListMH
{
    NodeMH *Head;
    NodeMH *Tail;
};

/* Khai bao cau truc dang DSLK don de chua danh sach Diem */
struct Diem
{
    int maSV;
    int maMH;
    float diem;
};
struct NodeDiem
{
    Diem info;
    struct NodeDiem *next;
};
struct ListD
{
    NodeDiem *Head;
    NodeDiem *Tail;
};

/* Khai bao cau truc dang DSLK don de chua danh sach BangDiem */
struct BangDiem
{
    int maSV;
    Diem ds[30];
    int smh;
    float diemTB, tongDiem;
};
struct NodeBD
{
    BangDiem info;
    struct NodeBD *next;
};
struct ListBD
{
    NodeBD *Head;
    NodeBD *Tail;
};

ListSV QSV;
ListMH QMH;
ListD QD;
ListBD QBD;

//================================================
// Dinh nghia cac thao tac voi danh sach sinh vien
bool ktMaSV(int k)
{
    string s = to_string(k);
    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i] == false))
            return false;
    }
    if (s.length() != 6)
        return false;
    return true;
}
NodeSV *TimSVMa(ListSV Q, int k)
{
    NodeSV *p;
    for (p = Q.Head; p != NULL; p = p->next)
        if (p->info.maSV == k)
            break;
    return p;
}

NodeSV *TimSVTen(ListSV Q, char s[])
{
    NodeSV *p;
    char s2[30];
    for (int i = 0; i < strlen(s); i++)
    {
        s[i] = tolower(s[i]);
    }

    for (p = Q.Head; p != NULL; p = p->next)
    {
        strncpy(s2, p->info.tenSV, 30); // copy s2 = tensv
        for (int i = 0; i < strlen(s2); i++)
        {
            s2[i] = tolower(s2[i]);
        }
        if (strcmp(s2, s) == 0)
            break;
    }
    return p;
}
void nhapSV(SinhVien &x)
{
    NodeSV *p;
    int k;
    do
    {
        printf("\nNhap ma Sinh vien gom 6 chu so: ");
        fflush(stdin);
        scanf("%d", &k);
        if (!ktMaSV(k))
            printf("\nMa Sinh vien khong hop le");
        p = TimSVMa(QSV, k);
        if (p != NULL)
            printf("\nMa Sinh vien da ton tai");
    } while (p != NULL || !ktMaSV(k));
    x.maSV = k;
    printf("Nhap ho ten: ");
    fflush(stdin);
    gets(x.tenSV);
}
void inSV(SinhVien x)
{
    printf("\nMa sinh vien: %-4d", x.maSV);
    printf("\nTen sinh vien: %-20s", x.tenSV);
    printf("\n");
}
int initSV(ListSV &Q)
{
    Q.Head = NULL;
    Q.Tail = NULL;
}

NodeSV *getNodeSV(SinhVien x)
{
    NodeSV *p;
    p = new NodeSV();
    if (p == NULL)
    {
        printf("\n Khong thanh cong");
        // exit(0);
    }
    p->info = x;
    p->next = NULL;
    return p;
}

void chenDauSV(ListSV &Q, NodeSV *p)
{
    if (Q.Head == NULL)
    {
        Q.Head = p;
        Q.Tail = p;
    }
    else
    {
        p->next = Q.Head;
        Q.Head = p;
    }
}
void nhapDSSV(ListSV &Q)
{
    int n, i;
    NodeSV *p;
    SinhVien x;
    printf("Nhap so sinh vien: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        nhapSV(x);
        p = getNodeSV(x);
        chenDauSV(Q, p);
    }
}
void inDSSV(ListSV Q)
{
    NodeSV *p;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        inSV(p->info);
    }
}

void inTongSV(ListSV Q)
{
    NodeSV *p;
    int n = 0;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        n++;
    }
    printf("\nTong so sinh vien: %-3d", n);
}

void luuFileSV(FILE *f, ListSV Q, char *nameF)
{
    f = fopen(nameF, "wb");
    int n = 0;
    NodeSV *p;
    if (f == NULL)
    {
        printf("\nLuu file khong thanh cong");
        fclose(f);
        return;
    }
    for (p = Q.Head; p != NULL; p = p->next)
        n = n + 1;
    fwrite(&n, sizeof(int), 1, f);
    for (p = Q.Head; p != NULL; p = p->next)
        fwrite(&p->info, sizeof(SinhVien), 1, f);
    fclose(f);
    printf("Luu file thanh cong\n");
}
void docFileSV(FILE *f, ListSV &Q, char *nameF)
{
    SinhVien x;
    int i, n;
    NodeSV *p;
    f = fopen(nameF, "rb");
    fread(&n, sizeof(int), 1, f);
    if (f == NULL)
    {
        printf("\nDoc file khong thanh cong");
        fclose(f);
        return;
    }
    for (int i = 0; i < n; i++)
    {
        fread(&x, sizeof(SinhVien), 1, f);
        p = getNodeSV(x);
        chenDauSV(Q, p);
    }
    fclose(f);
    printf("Doc file thanh cong!\n");
}

// Dinh  nghia cac thao tac voi mon hoc
bool ktMaMH(int k)
{
    string s = to_string(k);
    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i] == false))
            return false;
    }
    if (s.length() != 3)
        return false;
    return true;
}
NodeMH *TimMHMa(ListMH Q, int k)
{
    NodeMH *p;
    for (p = Q.Head; p != NULL; p = p->next)
        if (p->info.maMonHoc == k)
            break;
    return p;
}
NodeMH *TimMHTen(ListMH Q, char s[])
{
    NodeMH *p;
    char s2[20];
    for (int i = 0; i < strlen(s); i++)
    {
        s[i] = tolower(s[i]);
    }

    for (p = Q.Head; p != NULL; p = p->next)
    {
        strncpy(s2, p->info.tenMonHoc, 20); // copy s2 = tensv
        for (int i = 0; i < strlen(s2); i++)
        {
            s2[i] = tolower(s2[i]);
        }
        if (strcmp(s2, s) == 0)
            break;
    }
    return p;
}
void nhapMH(MonHoc &x)
{
    NodeMH *p;
    int k;
    do
    {
        printf("\nNhap ma Mon hoc gom 3 chu so: ");
        fflush(stdin);
        scanf("%d", &k);
        if (!ktMaMH(k))
            printf("\nMa mon hoc khong hop le");
        p = TimMHMa(QMH, k);
        if (p != NULL)
            printf("\nMa Mon hoc da ton tai");
    } while (p != NULL || !ktMaMH(k));
    x.maMonHoc = k;
    printf("Nhap ten mon hoc: ");
    fflush(stdin);
    gets(x.tenMonHoc);
    x.diemTB = 0.0;
}
void inMH(MonHoc x)
{
    printf("\nMa mon hoc: %-6d", x.maMonHoc);
    printf("Ten mon hoc: %-20s", x.tenMonHoc);
}
void inDTBMH(MonHoc x)
{
    printf("\nTen mon hoc: %-10s", x.tenMonHoc);
    printf("Diem trung binh: %-3.1f", x.diemTB);
}
void initDSMH(ListMH &Q)
{
    Q.Head = NULL;
    Q.Tail = NULL;
}
NodeMH *getNodeMH(MonHoc x)
{
    NodeMH *p;
    p = new NodeMH();
    if (p == NULL)
    {
        printf("\n Khong thanh cong");
        // exit(0);
    }
    p->info = x;
    p->next = NULL;
    return p;
};
void chenDauMH(ListMH &Q, NodeMH *p)
{
    if (Q.Head == NULL)
    {
        Q.Head = p;
        Q.Tail = p;
    }
    else
    {
        p->next = Q.Head;
        Q.Head = p;
    }
}
void nhapDSMH(ListMH &Q)
{
    int n, i;
    NodeMH *p;
    MonHoc x;
    printf("Nhap so mon hoc: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        nhapMH(x);
        p = getNodeMH(x);
        chenDauMH(Q, p);
    }
}
void inDSMH(ListMH Q)
{
    NodeMH *p;
    for (p = Q.Head; p != NULL; p = p->next)
        inMH(p->info);
}
int tongMH(ListMH Q)
{
    int sum = 0;
    for (NodeMH *p = Q.Head; p != NULL; p = p->next)
    {
        sum++;
    }
    return sum;
}
void inDSDTBMH(ListMH Q)
{
    NodeMH *p;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        printf("\nMon hoc: %-10s", p->info.tenMonHoc);
        printf("\nDiem trung binh: %-3.1f", p->info.diemTB);
    }
}
void inDSTongDiemMH(ListMH Q)
{
    NodeMH *p;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        printf("\n\nMon hoc: %-10s", p->info.tenMonHoc);
        printf("\nSo sinh vien: %-3d", p->info.ssv);
        printf("\nTong diem: %-3.1f", p->info.tongDiem);
    }
}
// tinh diem trung binh tung mon hoc
void tinhDTBMH(ListBD Q, ListMH &Q2)
{
    NodeBD *p;
    NodeMH *p2;
    int n;
    float tong;
    for (p2 = Q2.Head; p2 != NULL; p2 = p2->next)
    {
        tong = 0.0; // tong diem cua mon hoc
        n = 0;      // so hoc sinh hoc mon hoc
        for (p = Q.Head; p != NULL; p = p->next)
        {
            for (int i = 0; i < p->info.smh; i++)
            {
                if (p->info.ds[i].maMH == p2->info.maMonHoc)
                {
                    tong += p->info.ds[i].diem;
                    n++;
                }
            }
        }
        p2->info.diemTB = tong / n;
        p2->info.tongDiem = tong;
        p2->info.ssv = n;
    }
}

void inDTBTongSV(ListBD Q)
{
    NodeBD *p;
    float tong = 0.0, dtb;
    float n = 0.0;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        tong += p->info.diemTB;
        n++;
    }
    dtb = tong / n;
    printf("\nSo sinh vien co bang diem: %-3.0f", n);
    printf("\nDiem trung binh cua tat ca sinh vien: %-3.1f", dtb);
}

void inDSTongDiemSV(ListBD Q)
{
    NodeBD *p;
    NodeSV *p2;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        p2 = TimSVMa(QSV, p->info.maSV);
        printf("\n\nTen sinh vien: %-10s", p2->info.tenSV);
        printf("\nSo mon: %-3d", p->info.smh);
        printf("\nTong diem: %-3.1f", p->info.tongDiem);
    }
}

void sxMHThapCao(ListMH Q)
{
    tinhDTBMH(QBD, QMH);
    NodeMH *p, *q;
    MonHoc x;
    p = Q.Head;
    while ((p != NULL))
    {
        q = p->next;
        while (q != NULL)
        {
            if (p->info.diemTB > q->info.diemTB)
            {
                x = p->info;
                p->info = q->info;
                q->info = x;
            }
            q = q->next;
        }
        p = p->next;
    }
}
void sxMHCaoThap(ListMH Q)
{
    tinhDTBMH(QBD, QMH);
    NodeMH *p, *q;
    MonHoc x;
    p = Q.Head;
    while ((p != NULL))
    {
        q = p->next;
        while (q != NULL)
        {
            if (p->info.diemTB < q->info.diemTB)
            {
                x = p->info;
                p->info = q->info;
                q->info = x;
            }
            q = q->next;
        }
        p = p->next;
    }
}
void timMHDTBMax(ListMH Q)
{
    MonHoc x;
    sxMHCaoThap(Q);
    x = Q.Head->info;
    inDTBMH(x);
}
void timMHDTBMin(ListMH Q)
{
    MonHoc x;
    sxMHThapCao(Q);
    x = Q.Head->info;
    inDTBMH(x);
}
void timDSMHDTB(ListMH Q)
{
    tinhDTBMH(QBD, Q);
    NodeMH *p;
    float k;
    printf("\nNhap diem: ");
    scanf("%f", &k);
    printf("\nDanh sach mon hoc co diem trung binh lon hon %-2.0f:", k);
    for (p = Q.Head; p != NULL; p = p->next)
    {
        if (p->info.diemTB > k)
        {
            inDTBMH(p->info);
        }
    }
}
void luuFileMH(FILE *f, ListMH Q, char *nameF)
{
    f = fopen(nameF, "wb");
    int n = 0;
    NodeMH *p;
    if (f == NULL)
    {
        printf("\nLuu file khong thanh cong!");
        fclose(f);
        return;
    }
    for (p = Q.Head; p != NULL; p = p->next)
        n = n + 1;
    fwrite(&n, sizeof(int), 1, f);
    for (p = Q.Head; p != NULL; p = p->next)
        fwrite(&p->info, sizeof(MonHoc), 1, f);
    fclose(f);
    printf("Luu file thanh cong!");
}
void docFileMH(FILE *f, ListMH &Q, char *nameF)
{
    MonHoc x;
    int i, n;
    NodeMH *p;
    f = fopen(nameF, "rb");
    if (f == NULL)
    {
        printf("\nDoc file khong thanh cong!");
        fclose(f);
        return;
    }
    fread(&n, sizeof(int), 1, f);
    for (i = 0; i < n; i++)
    {
        fread(&x, sizeof(MonHoc), 1, f);
        p = getNodeMH(x);
        chenDauMH(Q, p);
    }
    fclose(f);
    printf("Doc file thanh cong!");
}

// Dinh nghia cac thao tac voi Diem
NodeDiem *TimDiem(ListD Q, int maSV, int maMH)
{
    NodeDiem *p;
    for (p = Q.Head; p != NULL; p = p->next)
        if (p->info.maSV == maSV && p->info.maMH == maMH)
            break;
    return p;
}
NodeDiem *TimDiemMon(ListD Q, int maMH)
{
    NodeDiem *p;
    for (p = Q.Head; p != NULL; p = p->next)
        if (p->info.maMH == maMH)
            break;
    return p;
}
void nhapDiem(Diem &x, float k)
{
    NodeMH *p;
    x.maSV = k;
    NodeDiem *p2;
    do
    {
        printf("\nNhap ma mon hoc: ");
        scanf("%d", &x.maMH);
        p = TimMHMa(QMH, x.maMH);
        if (p == NULL)
        {
            printf("\nBan nhap mon hoc chua co trong danh sach");
        }
        p2 = TimDiem(QD, x.maSV, x.maMH);
        if (p2 != NULL)
        {
            printf("\nMon hoc nay da co diem");
        }
    } while (p == NULL || p2 != NULL);
    do
    {
        printf("Nhap diem: ");
        scanf("%f", &x.diem);
        if (x.diem < 0 || x.diem > 10)
        {
            printf("\nDiem khong hop le, moi nhap lai");
        }
    } while (x.diem < 0 || x.diem > 10);
}

void inDiem(Diem x)
{
    NodeMH *p = TimMHMa(QMH, x.maMH);
    printf("\nMon: %-10s", p->info.tenMonHoc);
    printf("Diem: %-4.1f", x.diem);
}
void xoaDiem(ListD &Q, int maSV)
{
    NodeDiem *p = Q.Head, *q = NULL;
    while (p != NULL)
    {
        if (p->info.maSV == maSV)
            break;
        q = p;
        p = q->next;
    }
    if (p == NULL)
    {
        // printf("Khong tim thay ma sinh vien");
        return;
    }
    if (q != NULL)
    {
        if (p == Q.Tail)
            Q.Tail = q;
        q->next = p->next;
        free(p);
    }
    else
    {
        Q.Head = p->next;
        if (Q.Head == NULL)
            Q.Tail = NULL;
    }
}

/* Dinh  nghia cac thao tac voi Bang diem */
NodeBD *TimBDMaSV(ListBD Q, int k)
{
    NodeBD *p;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        if (p->info.maSV == k)
            break;
    }
    return p;
}
void nhapBangDiem(BangDiem &x)
{
    NodeBD *p2;
    int k;
    NodeSV *p;
    float tongDiem = 0.0;
    do
    {
        printf("\nNhap ma Sinh vien: ");
        scanf("%d", &k);
        p = TimSVMa(QSV, k);
        p2 = TimBDMaSV(QBD, k);
        if (p == NULL)
            printf("\nMa Sinh vien chua co trong danh sach");
        if (p2 != NULL)
            printf("\nSinh vien da co bang diem");
    } while (p == NULL || p2 != NULL);
    x.maSV = k;
    do
    {
        printf("Nhap so mon hoc (<=%d): ", tongMH(QMH));
        scanf("%d", &x.smh);
        if (x.smh > tongMH(QMH) || x.smh < 0)
            printf("\nSo mon hoc khong hop le");
    } while (x.smh > tongMH(QMH) || x.smh < 0);
    for (int i = 0; i < x.smh; i++)
    {
        nhapDiem(x.ds[i], x.maSV);
        tongDiem += x.ds[i].diem;
    }
    x.diemTB = tongDiem / x.smh;
    x.tongDiem = tongDiem;
}

void inBangDiem(BangDiem x)
{
    printf("\n");
    NodeSV *p;
    p = TimSVMa(QSV, x.maSV);
    inSV(p->info);
    printf("Tong so mon hoc: %d", x.smh);
    printf("\nDanh sach diem chi tiet:");
    for (int i = 0; i < x.smh; i++)
    {
        inDiem(x.ds[i]);
    }
    printf("\nDiem trung binh: %-4.1f", x.diemTB);
}
void inBDMaSV(ListBD Q)
{
    NodeSV *p;
    NodeBD *p2;
    int k;
    int tongDiem = 0;
    do
    {
        printf("\nNhap ma Sinh vien: ");
        scanf("%d", &k);
        p = TimSVMa(QSV, k);
        p2 = TimBDMaSV(QBD, k);
        if (p == NULL)
            printf("\nMa Sinh vien chua co trong danh sach");
    } while (p == NULL);
    if (p2 == NULL)
    {
        printf("\nMa Sinh vien chua co bang diem");
        return;
    }
    else
        inBangDiem(p2->info);
}
void inBDTenSV(ListBD Q)
{
    NodeSV *p;
    NodeBD *p2;
    char s[30];
    printf("\nNhap ten Sinh vien: ");
    fflush(stdin);
    gets(s);
    p = TimSVTen(QSV, s);
    if (p == NULL)
    {
        printf("\nSinh vien chua co trong danh sach");
        return;
    }
    p2 = TimBDMaSV(QBD, p->info.maSV);
    if (p2 == NULL)
    {
        printf("\nSinh vien chua co bang diem");
        return;
    }
    else
    {
        inBangDiem(p2->info);
    }
}
void initBangDiem(ListBD &Q)
{
    Q.Head = NULL;
    Q.Tail = NULL;
}

NodeBD *getNodeBD(BangDiem x)
{
    NodeBD *p;
    p = new NodeBD();
    if (p == NULL)
    {
        printf("\nKhong thanh cong");
        // exit(0);
    }
    p->info = x;
    p->next = NULL;
    return p;
}
void chenDauBD(ListBD &Q, NodeBD *p)
{
    if (Q.Head == NULL)
    {
        Q.Head = p;
        Q.Tail = p;
    }
    else
    {
        p->next = Q.Head;
        Q.Head = p;
    }
}
void NhapDSBD(ListBD &Q)
{
    int n, i;
    NodeBD *p;
    BangDiem x;
    printf("Nhap so Bang Diem: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        nhapBangDiem(x);
        p = getNodeBD(x);
        chenDauBD(Q, p);
    }
}
void ThemBD(ListBD &Q)
{
    NodeBD *p;
    BangDiem x;
    nhapBangDiem(x);
    p = getNodeBD(x);
    chenDauBD(Q, p);
}
void XoaBD(ListBD &Q)
{
    NodeBD *p = Q.Head, *q = NULL;
    int k;
    printf("Nhap ma sinh vien: ");
    scanf("%d", &k);
    while (p != NULL)
    {
        if (p->info.maSV == k)
            break;
        q = p;
        p = q->next;
    }
    if (p == NULL)
    {
        printf("Khong tim thay Bang diem");
        return;
    }
    if (q != NULL)
    {
        if (p == Q.Tail)
            Q.Tail = q;
        q->next = p->next;
        free(p);
    }
    else // p la phan tu dau danh sach
    {
        Q.Head = p->next;
        if (Q.Head == NULL)
            Q.Tail = NULL;
    }
    printf("\nXoa thanh cong!");
}
void SuaBD(ListBD &Q)
{
    NodeBD *p;
    int k;
    printf("Nhap ma sinh vien: ");
    scanf("%d", &k);
    NodeSV *p2 = TimSVMa(QSV, k);
    if (p2 == NULL)
    {
        printf("\nMa sinh vien khong ton tai");
        return;
    }
    for (p = Q.Head; p != NULL; p = p->next)
    {
        if (p->info.maSV == k)
        {
            xoaDiem(QD, k);
            printf("Sua diem:");
            do
            {
                printf("\nNhap so mon hoc (<%d): ", tongMH(QMH));
                scanf("%d", &p->info.smh);
                if (p->info.smh > tongMH(QMH) || p->info.smh < 0)
                    printf("\nSo mon hoc khong hop le");
            } while (p->info.smh > tongMH(QMH) || p->info.smh < 0);

            for (int i = 0; i < p->info.smh; i++)
            {
                nhapDiem(p->info.ds[i], p->info.maSV);
            }
            break;
        }
    }
}
void inDSBD(ListBD Q)
{
    NodeBD *p;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        inBangDiem(p->info);
    }
}
void inDTBSV(BangDiem x)
{
    NodeSV *p2 = TimSVMa(QSV, x.maSV);
    printf("\nTen sinh vien: %-20s", p2->info.tenSV);
    printf("\nDiem trung binh: %-3.1f", x.diemTB);
}
void inDSDTBSV(ListBD Q)
{
    NodeBD *p;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        printf("\n");
        inDTBSV(p->info);
    }
}
// SX hoan vi noi dung phan tu
void sxDTBThapCao(ListBD Q)
{
    NodeBD *p, *q;
    BangDiem x;
    p = Q.Head;
    while ((p != NULL))
    {
        q = p->next;
        while (q != NULL)
        {
            if (p->info.diemTB > q->info.diemTB)
            {
                x = p->info;
                p->info = q->info;
                q->info = x;
            }
            q = q->next;
        }
        p = p->next;
    }
}

void sxSVTen(ListSV Q)
{
    NodeSV *p, *q;
    SinhVien x;
    p = Q.Head;
    while ((p != NULL))
    {
        q = p->next;
        while (q != NULL)
        {
            if (p->info.tenSV > q->info.tenSV)
            {
                x = p->info;
                p->info = q->info;
                q->info = x;
            }
            q = q->next;
        }
        p = p->next;
    }
}
void sxDTBCaoThap(ListBD Q)
{
    NodeBD *p, *q;
    BangDiem x;
    p = Q.Head;
    while ((p != NULL))
    {
        q = p->next;
        while (q != NULL)
        {
            if (p->info.diemTB < q->info.diemTB)
            {
                x = p->info;
                p->info = q->info;
                q->info = x;
            }
            q = q->next;
        }
        p = p->next;
    }
}
void timBDDTBMax(ListBD Q)
{
    BangDiem x;
    sxDTBCaoThap(Q);
    x = Q.Head->info;
    inBangDiem(x);
}
void timBDDTBMin(ListBD Q)
{
    BangDiem x;
    sxDTBThapCao(Q);
    x = Q.Head->info;
    inBangDiem(x);
}
void inDSBDDTB(ListBD Q)
{
    float k;
    NodeBD *p;
    printf("\nNhap diem: ");
    scanf("%f", &k);
    printf("\nDanh sach sinh vien co diem trung binh lon hon %-2.0f:", k);
    for (p = Q.Head; p != NULL; p = p->next)
    {
        if (p->info.diemTB > k)
        {
            printf("\n");
            inDTBSV(p->info);
        }
    }
}
void demBDDTB(ListBD Q)
{
    float k;
    int kq=0;
    NodeBD *p;
    printf("\nNhap diem: ");
    scanf("%f", &k);
    
    for (p = Q.Head; p != NULL; p = p->next)
    {
        if (p->info.diemTB > k)
        {
            inBangDiem(p->info);
            kq+=1;
        }
    }
    printf("\nTong sinh vien co diem trung binh lon hon %-2.0f: %d", k,kq);
}

void demSVMH(ListBD Q)
{
    float k;
    int kq=0;
    NodeBD *p;
    printf("\nNhap so mon hoc: ");
    scanf("%f", &k);
    
    for (p = Q.Head; p != NULL; p = p->next)
    {
        if (p->info.smh > k)
        {
            inBangDiem(p->info);
            kq+=1;
        }
    }
    printf("\nTong sinh vien co so mon hoc lon hon %-2.0f: %d", k,kq);
}

void inDSDVDiemMH(ListBD Q)
{
    NodeBD *p;
    NodeSV *p2;
    NodeMH *p3;
    char tenMH[20];
    float diem;
    printf("\nNhap ten mon hoc: ");
    fflush(stdin);
    gets(tenMH);
    printf("Nhap diem: ");
    scanf("%f", &diem);
    p3 = TimMHTen(QMH, tenMH);
    if (p3 == NULL)
    {
        printf("Khong tim thay mon %s", tenMH);
    }
    else
    {

        printf("\nDanh sach sinh vien co diem mon %s lon hon %-2.0f:", p3->info.tenMonHoc, diem);
        for (p = Q.Head; p != NULL; p = p->next)
        {
            for (int i = 0; i < p->info.smh; i++)
            {
                if (p->info.ds[i].maMH == p3->info.maMonHoc && p->info.ds[i].diem > diem)
                {
                    p2 = TimSVMa(QSV, p->info.maSV);
                    printf("\n\nTen sinh vien: %-20s", p2->info.tenSV);
                    printf("\nMon hoc: %-10s", p3->info.tenMonHoc);
                    printf("\nDiem: %-2.1f", p->info.ds[i].diem);
                }
            }
        }
    }
}
void timMHDuoiDiem(ListBD Q, ListMH Q2)
{
    NodeBD *p;
    NodeMH *p2;
    int diem;
    bool v, v2 = false;

    printf("\nMoi nhap diem: ");
    scanf("%d", &diem);
    printf("\nDanh sach mon hoc khong co sinh vien duoi diem %d :", diem);
    for (p2 = Q2.Head; p2 != NULL; p2 = p2->next)
    {
        v = false;
        for (p = Q.Head; p != NULL; p = p->next)
        {
            for (int i = 0; i < p->info.smh; i++)
            {
                if ((p->info.ds[i].maMH == p2->info.maMonHoc) && (p->info.ds[i].diem < diem))
                {
                    v = true;
                }
            }
        }
        if (v == false)
        {
            printf("\n%s", p2->info.tenMonHoc);
            v2 = true;
        }
    }
    if (v2 == false)
        printf("\nKhong co mon nao!");
}

void timBDuoiDiem(ListBD Q, ListMH Q2, ListSV Q3)
{
    NodeBD *p;
    NodeMH *p2;
    NodeSV *p3;
    float diem;
    int n = 0, m = 0;
    printf("\nMoi ban nhap diem: ");
    scanf("%f", &diem);
    printf("\nDanh sach sinh vien co diem duoi %-2.0f:", diem);
    for (p = Q.Head; p != NULL; p = p->next)
    {
        n = 0;
        for (int i = 0; i < p->info.smh; i++)
        {
            if (p->info.ds[i].diem < diem)
            {
                p2 = TimMHMa(Q2, p->info.ds[i].maMH);
                p3 = TimSVMa(Q3, p->info.maSV);
                if (n == 0)
                {
                    printf("\n\nTen sinh vien: %-20s", p3->info.tenSV);
                }
                printf("\nMon hoc: %-10sDiem: %-2.1f", p2->info.tenMonHoc, p->info.ds[i].diem);
                // printf("\nDiem: %d", p->info.ds[i].diem);
                n++;
                m++;
            }
        }
    }
    if (m == 0)
        printf("\nKhong co sinh vien nao");
}
void luuFileBD(FILE *f, ListBD Q, char *nameF)
{
    f = fopen(nameF, "wb");
    int n = 0;
    NodeBD *p;
    for (p = Q.Head; p != NULL; p = p->next)
        n++;
    fwrite(&n, sizeof(int), 1, f);
    for (p = Q.Head; p != NULL; p = p->next)
        fwrite(&p->info, sizeof(BangDiem), 1, f);
    fclose(f);
    printf("\nLuu file thanh cong!");
}
void docFileBD(FILE *f, ListBD &Q, char *nameF)
{
    BangDiem x;
    int i, n;
    NodeBD *p;
    f = fopen(nameF, "rb");
    if (f == NULL)
    {
        printf("\nDoc file khong thanh cong");
        fclose(f);
        return;
    }
    fread(&n, sizeof(int), 1, f);
    for (int i = 0; i < n; i++)
    {
        fread(&x, sizeof(BangDiem), 1, f);
        p = getNodeBD(x);
        chenDauBD(Q, p);
    }
    fclose(f);
    printf("Doc file thanh cong!");
}
/* Tao menu giao dien */
void Menu1(FILE *f)
{
    int chon;
    do
    {
        cout << "\n-------------- Menu 1 --------------------";
        cout << "\n|1.Nhap danh sach Sinh vien";
        cout << "\n|2.In danh sach Sinh vien";
        cout << "\n|3.Luu file danh sach Sinh vien";
        cout << "\n|4.Doc file danh sach Sinh vien";
        cout << "\n|";
        cout << "\n|5.Nhap danh sach Mon hoc";
        cout << "\n|6.In danh sach Mon hoc";
        cout << "\n|7.Luu file danh sach Mon hoc";
        cout << "\n|8.Doc file danh sach Mon hoc";
        cout << "\n|";
        cout << "\n|9.Nhap danh sach Bang diem";
        cout << "\n|10.In danh sach Bang diem";
        cout << "\n|11.Luu file danh sach Bang diem";
        cout << "\n|12.Doc file danh sach Bang diem";
        cout << "\n|13.Quay lai menu chinh";
        cout << "\n|0.Thoat";
        cout << "\n--------------------------------------------";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            nhapDSSV(QSV);
            break;
        case 2:
            inDSSV(QSV);
            break;
        case 3:
            luuFileSV(f, QSV, "dssv.txt");
            break;
        case 4:
            docFileSV(f, QSV, "dssv.txt");
            break;
        case 5:
            nhapDSMH(QMH);
            break;
        case 6:
            inDSMH(QMH);
            break;
        case 7:
            luuFileMH(f, QMH, "dsmh.txt");
            break;
        case 8:
            docFileMH(f, QMH, "dsmh.txt");
            break;
        case 9:
            NhapDSBD(QBD);
            break;
        case 10:
            inDSBD(QBD);
            break;
        case 11:
            luuFileBD(f, QBD, "dsbd.txt");
            break;
        case 12:
            docFileBD(f, QBD, "dsbd.txt");
            break;
        case 13:
            return;
            break;
        case 0:
            cout << "Cam on!";
            exit(0);
        default:
            cout << "Moi ban chon lai";
            break;
        }
    } while (chon != 0);
}
void Menu2()
{
    int chon;
    do
    {
        cout << "\n------------- Menu 2 ----------------------";
        cout << "\n|1.Them bang diem";
        cout << "\n|2.Sua bang diem";
        cout << "\n|3.Xoa bang diem";
        cout << "\n|4.Quay lai menu chinh";
        cout << "\n|0. Thoat";
        cout << "\n-------------------------------------------";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            ThemBD(QBD);
            break;
        case 2:
            SuaBD(QBD);
            break;
        case 3:
            XoaBD(QBD);
            break;
        case 4:
            return;
            break;
        case 0:
            cout << "Cam on!";
            exit(0);
        default:
            cout << "Moi ban chon lai";
            break;
        }
    } while (chon != 0);
}
void Menu3()
{
    int chon;
    do
    {
        cout << "\n---------------- Menu 3 -------------------";
        cout << "\n|1.Tim bang diem theo Ma sinh vien";
        cout << "\n|2.Tim bang diem theo Ten sinh vien";
        cout << "\n|3.Quay lai menu chinh";
        cout << "\n|0. Thoat";
        cout << "\n-------------------------------------------";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            inBDMaSV(QBD);
            break;
        case 2:
            inBDTenSV(QBD);
            break;
        case 3:
            return;
            break;
        case 0:
            cout << "Cam on!";
            exit(0);
        default:
            cout << "Moi ban chon lai";
            break;
        }
    } while (chon != 0);
}
void Menu4()
{
    int chon;
    do
    {
        cout << "\n----------------------- Menu 4 ---------------------------";
        cout << "\n|1.Sap xep sinh vien co diem trung binh tu thap den cao";
        cout << "\n|2.Sap xep sinh vien co diem trung binh tu cao den thap";
        cout << "\n|3.Sap xep mon co diem trung binh tu thap den cao";
        cout << "\n|4.Sap xep mon co diem trung binh tu cao den thap";
        cout << "\n|5.Quay lai menu chinh";
        cout << "\n|6.Sap xep sinh vien theo ten";
        cout << "\n|0. Thoat";
        cout << "\n-----------------------------------------------------------";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            sxDTBThapCao(QBD);
            cout << "Danh sach sinh vien co diem trung binh tu thap den cao:";
            inDSDTBSV(QBD);
            break;
        case 2:
            sxDTBCaoThap(QBD);
            cout << "Danh sach sinh vien co diem trung binh tu cao den thap:";
            inDSDTBSV(QBD);
            break;
        case 3:
            sxMHThapCao(QMH);
            cout << "Danh sach mon hoc co diem trung binh tu thap den cao:";
            inDSDTBMH(QMH);
            break;
        case 4:
            sxMHCaoThap(QMH);
            cout << "Danh sach mon hoc co diem trung binh tu cao den thap:";
            inDSDTBMH(QMH);
            break;
        case 5:
            return;
            break;
        case 6:
        sxSVTen(QSV);
        inDSSV(QSV);
        break;
        case 0:
            cout << "Cam on!";
            exit(0);
        default:
            cout << "Moi ban chon lai";
            break;
        }
    } while (chon != 0);
}
void Menu5()
{
    int chon;
    do
    {
        cout << "\n-------------------- Menu 5 ------------------------";
        cout << "\n|1.Tim sinh vien co diem trung binh cao nhat";
        cout << "\n|2.Tim sinh vien co diem trung binh thap nhat";
        cout << "\n|3.Tim mon hoc co diem trung binh cao nhat";
        cout << "\n|4.Tim mon hoc co diem trung binh thap nhat";
        cout << "\n|5.Quay lai menu chinh";
        cout << "\n|0. Thoat";
        cout << "\n----------------------------------------------------";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            cout << "Sinh vien co diem trung binh cao nhat:";
            timBDDTBMax(QBD);
            break;
        case 2:
            cout << "Sinh vien co diem trung binh thap nhat:";
            timBDDTBMin(QBD);
            break;
        case 3:
            cout << "Mon hoc co diem trung binh cao nhat:\n";
            timMHDTBMax(QMH);
            break;
        case 4:
            cout << "Mon hoc co diem trung binh thap nhat:\n";
            timMHDTBMin(QMH);
            break;
        case 5:
            return;
            break;
        case 0:
            cout << "Cam on!";
            exit(0);
        default:
            cout << "Moi ban chon lai";
            break;
        }
    } while (chon != 0);
}
void Menu6()
{
    int chon;
    do
    {
        cout << "\n---------------------- Menu 6 ----------------------";
        cout << "\n|1.Tinh tong diem cua tung mon hoc";
        cout << "\n|2.Tinh tong diem cua tung sinh vien";
        cout << "\n|3.Tinh diem trung binh cua tung sinh vien";
        cout << "\n|4.Tinh diem trung binh cua tat ca sinh vien";
        cout << "\n|5.Dem tong so sinh vien";
        cout << "\n|7.Dem tong so sinh vien co diem trung binh lon hon so nhap vao";
        cout << "\n|6.Quay lai menu chinh";
        cout << "\n|0. Thoat";
        cout << "\n----------------------------------------------------";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            tinhDTBMH(QBD, QMH);
            cout << "Tong diem cua tung mon hoc: ";
            inDSTongDiemMH(QMH);
            break;
        case 2:
            tinhDTBMH(QBD, QMH);
            cout << "Tong diem cua tung sinh vien:";
            inDSTongDiemSV(QBD);
            break;
        case 3:
            cout << "Diem trung binh cua tung sinh vien:";
            inDSDTBSV(QBD);
            break;
        case 4:
            cout << "Diem trung binh cua tat ca sinh vien:";
            inDTBTongSV(QBD);
            break;
        case 5:
            inTongSV(QSV);
            break;
        case 6:
            return;
            break;
        case 7:
            demSVMH(QBD);
            break;


        case 0:
            cout << "Cam on!";
            exit(0);
        default:
            cout << "Moi ban chon lai";
            break;
        }
    } while (chon != 0);
}
void Menu7()
{
    int chon;
    do
    {
        cout << "\n-------------------------- Menu 7 ----------------------------";
        cout << "\n|1.DS sinh vien co diem trung binh lon hon so nhap vao";
        cout << "\n|2.DS mon hoc co diem trung binh lon hon so nhap vao";
        cout << "\n|3.DS sinh vien co diem lon hon so nhap vao cua ten mon hoc nhap vao";
        cout << "\n|4.DS mon hoc khong co sinh vien duoi diem nhap vao";
        cout << "\n|5.DS sinh vien co diem mon bat ky duoi diem nhap vao";
        cout << "\n|6.Quay lai menu chinh";
        cout << "\n|0. Thoat";
        cout << "\n---------------------------------------------------------------";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            inDSBDDTB(QBD);
            break;
        case 2:
            timDSMHDTB(QMH);
            break;
        case 3:
            inDSDVDiemMH(QBD);
            break;
        case 4:
            timMHDuoiDiem(QBD, QMH);
            break;
        case 5:
            timBDuoiDiem(QBD, QMH, QSV);
            break;
        case 6:
            return;
            break;
        case 0:
            cout << "Cam on!";
            exit(0);
        default:
            cout << "Moi ban chon lai";
            break;
        }
    } while (chon != 0);
}
void MenuChinh()
{
    FILE *f;
    int chon;
    do
    {
        cout << "\n=================================================";
        cout << "\n|\t\tQUAN LY DIEM SINH VIEN";
        cout << "\n|1. Nhap-In danh sach doi tuong; Doc va luu file";
        cout << "\n|2. Them, sua, xoa doi tuong";
        cout << "\n|3. Tim kiem doi tuong";
        cout << "\n|4. Sap xep doi tuong";
        cout << "\n|5. Tim phan tu lon nhat, nho nhat";
        cout << "\n|6. Tinh tong, trung binh, dem";
        cout << "\n|7. Thong ke theo dieu kien";
        cout << "\n|0. Thoat";
        cout << "\n=================================================";
        cout << "\nChon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            Menu1(f);
            break;
        case 2:
            Menu2();
            break;
        case 3:
            Menu3();
            break;
        case 4:
            Menu4();
            break;
        case 5:
            Menu5();
            break;
        case 6:
            Menu6();
            break;
        case 7:
            Menu7();
            break;
        case 0:
            cout << "Cam on!";
            exit(0);
        default:
            cout << "Moi ban chon lai";
            break;
        }
    } while (chon != 0);
}
//================================================
int main()
{
    MenuChinh();
}