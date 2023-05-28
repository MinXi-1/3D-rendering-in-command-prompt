#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define PI 3.14159265
#include<malloc.h>
#define BM 19778				// 位图的标志
#define PIF "default-base-color.bmp"
#define ushort unsigned short
#define uint unsigned int
#define uchar unsigned char
const int SCREEN_WIDTH = 30;
const int SCREEN_HEIGHT = 30;
// 判断是否是位图,在0-1字节
int IsBitMap(FILE * fp)
{
	ushort s;
	fread(&s, 1, 2, fp);
	return s == BM ? 1 : 0;
}

// 获得图片的宽度,在18-21字节
int getWidth(FILE * fp)
{
	int width;
	fseek(fp, 18, SEEK_SET);
	fread(&width, 1, 4, fp);
	return width;
}

// 获得图片的高度 ，在22-25字节
int getHeight(FILE * fp)
{
	int height;
	fseek(fp, 22, SEEK_SET);
	fread(&height, 1, 4, fp);
	return height;
}

// 获得每个像素的位数,在28-29字节
ushort getBit(FILE * fp)
{
	ushort bit;
	fseek(fp, 28, SEEK_SET);
	fread(&bit, 1, 2, fp);
	return bit;
}

// 获得数据的起始位置，在10-13字节
uint getOffSet(FILE * fp)
{
	uint OffSet;
	fseek(fp, 10L, SEEK_SET);
	fread(&OffSet, 1, 4, fp);
	return OffSet;
}

uint getP(FILE * fp, int i, int j, int c)
{
	uchar p = 0;
	uint w = getWidth(fp);
	uint h = getHeight(fp);
	if (j > h)
	{
		j = h;
	}
	if (j < 1)
	{
		j = 1;
	}
	if (i > w)
	{
		i = w;
	}
	if (i < 1)
	{
		i = 1;
	}
	uint r = 3 * i + j * ceil((w * 3) / 4.0) * 4;
	switch (c)
	{
	case 1:
		fseek(fp, getOffSet(fp) + r + 1, 0);
		break;
	case 2:
		fseek(fp, getOffSet(fp) + r + 2, 0);
		break;
	case 3:
		fseek(fp, getOffSet(fp) + r + 3, 0);
		break;
	}
	fread(&p, 1, 2, fp);
	return p;
}

struct Data
{
	int bi;
	int sz1;
	int sz2;
	int m;
	int fr;
	int w;
	int h;
	int *arr;
	int *p;
	int *p1;
	int wh;
	double a;
	double b;
	float *dx;
	float *dz;
	float *dy;
	float *mf;
	double *tf;
	double *tf1;
	float *zz;
	float *x;
	float *z;
	float *y;
	float *sx;
	float *sy;
	int *t;
	int *k;
	int *su;
	int *zu;
	float *lm;
	int r[128][16][16];
	float l[128][14];
	float lz[128][3];
	float s;
	int sj;
	float xb;
	float yb;
	float zb;
	int bs;
	int lt;
	int bt;
	int bt1;
	int yt;
	int tu;
	float ft;
	int ft1;
}
stu;
void initialize()
{
	stu.w = SCREEN_WIDTH;
	stu.h = SCREEN_HEIGHT;
	int zd = 300000;
	int zm = zd / 3;
	stu.m = 0;
	stu.wh = stu.w * stu.h;
	int *p1 = (int *)malloc(sizeof(int) * stu.wh);
	stu.p1 = p1;
	int *p = (int *)malloc(sizeof(int) * stu.wh);
	stu.arr = p;
	float *x = (float *)malloc(sizeof(int) * zd);
	stu.x = x;
	float *y = (float *)malloc(sizeof(int) * zd);
	stu.z = y;
	float *z = (float *)malloc(sizeof(int) * zd);
	stu.y = z;
	float *dx = (float *)malloc(sizeof(int) * zd);
	stu.dx = dx;
	float *dy = (float *)malloc(sizeof(int) * zd);
	stu.dz = dy;
	float *dz = (float *)malloc(sizeof(int) * zd);
	stu.dy = dz;
	float *mf = (float *)malloc(sizeof(int) * zd * 3);
	stu.mf = mf;
	double *tf = (double *)malloc(sizeof(int) * zd * 3);
	stu.tf = tf;
	double *tf1 = (double *)malloc(sizeof(int) * zd * 6);
	stu.tf1 = tf1;
	float *zz = (float *)malloc(sizeof(int) * zm);
	stu.zz = zz;
	float *sx = (float *)malloc(sizeof(int) * zd);
	stu.sx = sx;
	float *sy = (float *)malloc(sizeof(int) * zd);
	stu.sy = sy;
	int *t = (int *)malloc(sizeof(int) * zm);
	stu.t = t;
	int *k = (int *)malloc(sizeof(int) * zm);
	stu.k = k;
	int *su = (int *)malloc(sizeof(int) * zm);
	stu.su = su;
	int *zu = (int *)malloc(sizeof(int) * zm);
	stu.zu = zu;
	float *lm = (float *)malloc(sizeof(int) * zd);
	stu.lm = lm;
}

void f1()
{
	int v = -1;
	int f = -1;
	int vt = -1;
	FILE *file = fopen("caiquan.obj", "r");
	char str[2];
	char strm[2];
	char strm1[2];
	char str1[4];
	char str3[1];
	int l;
	int d = 0;
	fseek(file, 1, 2);
	int zp = ftell(file) - 2;
	fseek(file, 0, 0);
	char a;
	while (feof(file) == 0 && ftell(file) < zp)
	{
		fgets(str, 2, file);
		if (strcmp(str, "#") == 0)
		{
			while (strcmp(str, "\n") != 0)
			{
				fgets(str, 2, file);
			}
		}
		else
		{
			fseek(file, ftell(file) - 1, 0);
			int i = 0;
			fgets(str, 2, file);
			fseek(file, ftell(file) - 1, 0);
			while (strcmp(str, "\n") != 0)
			{
				l = 0;
				fgets(str, 2, file);
				while (strcmp(str, " ") != 0 && strcmp(str, "\n") != 0 && strcmp(str, "/") != 0)
				{
					fgets(str, 2, file);
					l++;
				}
				fseek(file, ftell(file) - 1 - l, 0);
				char str2[l];
				fgets(str2, l + 1, file);
				if (i == 0)
				{
					d = 0;
					if (strcmp(str2, "v") == 0)
					{
						d = 1;
						v++;
					}
					if (strcmp(str2, "vt") == 0)
					{
						d = 2;
						vt++;
					}
					if (strcmp(str2, "f") == 0)
					{
						d = 3;
						f++;
					}
					if (strcmp(str2, "g") == 0)
					{
						d = 4;
					}
					if (strcmp(str2, "mtllib") == 0)
					{
						d = 5;
					}
					if (strcmp(str2, "usemtl") == 0)
					{
						d = 6;
					}
					if (strcmp(str2, "vn") == 0)
					{
						d = 7;
					}
				}
				else
				{
					switch (d)
					{
					case 1:
						{
							stu.mf[v * 3 + i] = strtod(str2, NULL);
						}
					case 2:
						{
							stu.tf[vt * 3 + i] = strtod(str2, NULL);
						}
					case 3:
						{
							int im = i / 2;
							int ix = i % 2;
							int z = atoi(str2) - 1;
							if (ix == 1)
							{
								if (im == 3)
								{
									f++;
									stu.x[f * 3] = stu.mf[z * 3 + 1];
									stu.y[f * 3] = stu.mf[z * 3 + 2];
									stu.z[f * 3] = stu.mf[z * 3 + 3];
									stu.x[f * 3 + 1] = stu.x[(f - 1)];
									stu.y[f * 3 + 1] = stu.y[(f - 1)];
									stu.z[f * 3 + 1] = stu.z[(f - 1)];
									stu.x[f * 3 + 2] = stu.x[(f - 2)];
									stu.y[f * 3 + 2] = stu.y[(f - 2)];
									stu.z[f * 3 + 2] = stu.z[(f - 2)];
								}
								else
								{
									stu.x[f * 3 + im] = stu.mf[z * 3 + 1];
									stu.y[f * 3 + im] = stu.mf[z * 3 + 2];
									stu.z[f * 3 + im] = stu.mf[z * 3 + 3];
								}
							}
							if (ix == 0)
							{
								if (im == 4)
								{
									stu.tf1[(f * 3 + im - 1) * 2] = stu.tf[z * 3 + 1];
									stu.tf1[(f * 3 + im - 1) * 2 + 1] = stu.tf[z * 3 + 2];
									stu.tf1[(f * 3 + im - 1) * 2 + 2] = stu.tf1[f * 3 - 2];
									stu.tf1[(f * 3 + im - 1) * 2 + 3] = stu.tf1[f * 3 - 1];
									stu.tf1[(f * 3 + im - 1) * 2 + 4] = stu.tf1[f * 3 - 4];
									stu.tf1[(f * 3 + im - 1) * 2 + 5] = stu.tf1[f * 3 - 3];
								}
								else
								{
									stu.tf1[(f * 3 + im - 1) * 2] = stu.tf[z * 3 + 1];
									stu.tf1[(f * 3 + im - 1) * 2 + 1] = stu.tf[z * 3 + 2];
								}
							}
						}
					}
				}
				fgets(str, 2, file);
				if (strcmp(str, " ") == 0)
				{
					while (strcmp(str, " ") == 0)
					{
						fgets(str, 2, file);
					}
					fgets(str, 2, file);
					fseek(file, ftell(file) - 2, 0);
				}
				i++;
			}
		}
	}
	stu.m = f;
	fclose(file);
}

void swap(int a[], int low, int high)
{
	int t = a[low];
	int m = stu.su[low];
	a[low] = a[high];
	stu.su[low] = stu.su[high];
	stu.su[high] = m;
	a[high] = t;
}

int partition(int a[], int low, int high)
{
	int point = a[low];
	while (low < high)
	{
		while (low < high && a[high] >= point)
		{
			high--;
		}
		swap(a, low, high);
		while (low < high && a[low] <= point)
		{
			low++;
		}
		swap(a, low, high);
	}
	return low;
}

void quicksort(int a[], int low, int high)
{
	if (low < high)
	{
		int point = partition(a, low, high);
		quicksort(a, low, point - 1);
		quicksort(a, point + 1, high);
	}
}

int MAX(int a, int b, int c)
{
	if (a >= b && a >= c)
	{
		return a;
	}
	else if (c >= a && c >= b)
	{
		return c;
	}
	else
	{
		return b;
	}
}

int MIN(int a, int b, int c)
{
	if (a <= b && a <= c)
	{
		return a;
	}
	else if (c <= a && c <= b)
	{
		return c;
	}
	else
	{
		return b;
	}
}

float min(float a, float c, float b)
{
	if (a < b)
	{
		return c;
	}
	else
	{
		return b;
	}
}

int xz(float x, float z, int n)
{
	int s = stu.s;
	if (n != 0)
	{
		s = stu.l[n][10];
		int f = stu.l[n][12];
		if (f == 1)
		{
			return x * s;
		}
		else
		{
			return x * s / z;
		}
	}
	else
	{
		return x * s / z;
	}
}

int co(int cl)
{
	if (cl > 255)
	{
		return 255;
	}
	if (cl < 0)
	{
		return 0;
	}
	return cl;
}

void Triangle(float xa, float ya, float xb, float yb, float xc, float yc, int t, int fr, int tu)
{
	double a11 = cos(stu.a * PI / 180);
	double a12 = sin(stu.a * PI / 180);
	double b11 = cos(stu.b * PI / 180);
	double b12 = sin(stu.b * PI / 180);
	FILE *fp = fopen(PIF, "r");
	int tw = getWidth(fp);
	int th = getHeight(fp);
	float axm = stu.tf1[t * 6] * tw;
	float aym = stu.tf1[t * 6 + 1] * th;
	float bxm = stu.tf1[t * 6 + 2] * tw;
	float bym = stu.tf1[t * 6 + 3] * th;
	float cxm = stu.tf1[t * 6 + 4] * tw;
	float cym = stu.tf1[t * 6 + 5] * th;
	float abxm = -axm + bxm;
	float abym = -aym + bym;
	float abm = sqrt(abxm * abxm + abym * abym);
	abxm = abxm / abm;
	abym = abym / abm;
	float cbxm = -cxm + bxm;
	float cbym = -cym + bym;
	float cbm = sqrt(cbxm * cbxm + cbym * cbym);
	cbxm = cbxm / cbm;
	cbym = cbym / cbm;
	int lp = stu.k[t];
	float ax = stu.dx[t * 3];
	float bx = stu.dx[t * 3 + 1];
	float cx = stu.dx[t * 3 + 2];
	float ay = stu.dy[t * 3];
	float by = stu.dy[t * 3 + 1];
	float cy = stu.dy[t * 3 + 2];
	float x1 = (bx - ax) / abm;
	float y1 = (by - ay) / abm;
	float x2 = (bx - cx) / cbm;
	float y2 = (by - cy) / cbm;
	float xn1 = (bx - ax);
	float yn1 = (by - ay);
	float xn2 = (bx - cx);
	float yn2 = (by - cy);
	float az = stu.dz[t * 3];
	float bz = stu.dz[t * 3 + 1];
	float cz = stu.dz[t * 3 + 2];
	float z1 = bz - az;
	float z2 = bz - cz;
	float zn1 = z1 / abm;
	float zn2 = z2 / cbm;
	float a2 = x1 + y1 + zn1;
	float a3 = x2 + y2 + zn2;
	int wx1 = MAX(xa, xb, xc);
	int wx2 = MIN(xa, xb, xc);
	int wy1 = MAX(ya, yb, yc);
	int wy2 = MIN(ya, yb, yc);
	int h = stu.h;
	int w = stu.w;
	int sz1 = stu.sz1;
	int sz2 = stu.sz2;
	if (tu != 0)
	{
		h = stu.l[tu][6];
		w = stu.l[tu][7];
		sz1 = stu.l[tu][8];
		sz2 = stu.l[tu][9];
	}
	if (wy1 > h / 2)
	{
		wy1 = h / 2 + 1;
	}
	if (wx1 > w / 2)
	{
		wx1 = w / 2;
	}
	if (wx2 < -w / 2)
	{
		wx2 = -w / 2;
	}
	if (wy2 < -h / 2)
	{
		wy2 = -h / 2;
	}
	int y = wy2;
	float a;
	float b;
	float c;
	float wx = yn1 * z2 - z1 * yn2;
	float wy = z1 * xn2 - xn1 * z2;
	float wz = xn1 * yn2 - yn1 * xn2;
	float ln = sqrt(wx * wx + wy * wy + wz * wz);
	wx = wx / ln;
	wy = wy / ln;
	wz = wz / ln;
	int x;
	int draw;
	float zt;
	float yt;
	float xt;
	float tx;
	float ty;
	float tz;
	float f;
	float u;
	float v;
	int ac;
	int bc;
	int cc;
	float a1;
	while (y < wy1)
	{
		x = wx2;
		while (x < wx1)
		{
			a = (-(x - xb) * (yc - yb) + (y - yb) * (xc - xb)) / (-(xa - xb) * (yc - yb) +
																  (ya - yb) * (xc - xb));
			b = (-(x - xc) * (ya - yc) + (y - yc) * (xa - xc)) / (-(xb - xc) * (ya - yc) +
																  (yb - yc) * (xa - xc));
			c = 1 - a - b;
			if (a >= -0.001 && b >= -0.001 && c >= -0.001)
			{
				draw = (h / 2 - y) * w + x + w / 2;
				if (tu != 0)
				{
					draw = draw + stu.bt1;
				}
				zt = 1 / (a / az + b / bz + c / cz);
				yt = (zt * y) / stu.s;
				xt = (zt * x) / stu.s;
				tx = bx - xt;
				ty = by - yt;
				tz = bz - zt;
				a1 = tx + ty + tz;
				f = (wx * xt + wy * yt + wz * zt);
				u = (a3 * tx - a1 * x2) / (a3 * x1 - a2 * x2);
				v = (a2 * tx - a1 * x1) / (a2 * x2 - a3 * x1);
				if (u < 0)
				{
					u = 0;
				}
				if (v < 0)
				{
					v = 0;
				}
				if (u > abm)
				{
					u = abm;
				}
				if (v > cbm)
				{
					v = cbm;
				}
				if (zt > stu.sz1 && zt < stu.sz2 && zt > 0 && f > 0)
				{
					ac;
					bc;
					cc;
					if (fr == 0 || fr == -1)
					{
						float zzm = stu.z[t * 3 + 1];
						float zym = stu.y[t * 3 + 1];
						float zxm = stu.x[t * 3 + 1];
						float dx =
							zxm - u * (zxm - stu.x[t * 3]) / abm - v * (zxm -
																		stu.x[t * 3 + 2]) / cbm;
						float dy =
							zym - u * (zym - stu.y[t * 3]) / abm - v * (zym -
																		stu.y[t * 3 + 2]) / cbm;
						float dz =
							zzm - u * (zzm - stu.z[t * 3]) / abm - v * (zzm -
																		stu.z[t * 3 + 2]) / cbm;
						int lt = 1;
						int bt = stu.wh;
						float mx;
						float my;
						float mz;
						float mx1;
						float my1;
						int r = 0;
						int g = 0;
						int b = 0;
						float px;
						float py;
						int zd;

						float lmn1 = sqrt(xt * xt + yt * yt + zt * zt);

						float xt1 = xt / lmn1;
						float yt1 = yt / lmn1;
						float zt1 = zt / lmn1;

						float ft = wx * xt1 + wy * yt1 + wz * zt1;


						int n = 1;
						float xf = 0;
						float yf = 0;
						float zf = 0;
						int fc;
						fc = 0x000000;
						int r1 = 2 * fc / 0x10000;
						int g1 = 2 * (fc / 0x100) % 256;
						int b1 = 2 * fc % 256;
						while (lt <= stu.lt)
						{
							float lx = stu.l[lt][1]-stu.xb;
							float ly = stu.l[lt][3]-stu.zb;
							float lz = stu.l[lt][2]-stu.yb;
							float lx1 = a11 * lx - a12 * lz;
							lz = a12 * lx + a11 * lz;
							float ly1 = b11 * ly + b12 * lz;
							lz = b11 * lz - b12 * ly;
							lx1=-lx1+xt;
							ly1=-ly1+yt;
							lz=-lz+zt;
							float lmn = sqrt(lx1 * lx1 + ly1 * ly1 + lz * lz);
							float xl = lx1 / lmn;
							float yl = ly1 / lmn;
							float zl = lz / lmn;
							float wx1 = xl + xt1;
							float wy1 = yl + yt1;
							float wz1 = zl + zt1;
							float lmn2 = sqrt(wx1 * wx1 + wy1 * wy1 + wz1 * wz1);
							wx1 = wx1 / lmn2;
							wy1 = wy1 / lmn2;
							wz1 = wz1 / lmn2;
							float ftx = xt1 - 2 * wx1 * ft;
							float fty = yt1 - 2 * wy1 * ft;
							float ftz = zt1 - 2 * wz1 * ft;
							r = r + stu.l[lt][12];
							g = g + stu.l[lt][12];
							b = b + stu.l[lt][12];
							int l = stu.l[lt][11];
							mx = dx - stu.l[lt][1];
							my = dy - stu.l[lt][3];
							mz = dz - stu.l[lt][2];
							double a1 = cos(stu.l[lt][4] * PI / 180);
							double a2 = sin(stu.l[lt][4] * PI / 180);
							double b1 = cos(stu.l[lt][5] * PI / 180);
							double b2 = sin(stu.l[lt][5] * PI / 180);
							mx1 = a1 * mx - a2 * mz;
							mz = a2 * mx + a1 * mz;
							my1 = b1 * my + b2 * mz;
							mz = b1 * mz - b2 * my;
							px = xz(mx1, mz, lt) + stu.l[lt][6] / 2;
							py = stu.l[lt][7] / 2 - xz(my1, mz, lt);
							if (px < 0 || px > stu.l[lt][6] || py < 0 || py > stu.l[lt][7]||mz<0)
							{
								zd = 1;

							}
							else
							{
								zd = 0;
								int p = py * stu.l[lt][6] + px + bt;
								if (stu.yt == 1)
								{
									r = r + l / 0x10000 / 50.0 * stu.l[lt][12];
									g = g + (l / 0x100) % 256 / 50.0 * stu.l[lt][12];
									b = b + (l % 256) / 50.0 * stu.l[lt][12];
									float ztp = stu.lm[p];
									float m =
										stu.l[lt][12] * 500 * (wx * xl + wy * yl +
															   wz * zl) / (lmn1 * lmn1);
									if (ztp >= mz - 5 && m > 0)
									{

										float k = 10 * pow(100,
														   0.5 * -min(1, 1,
																	  sqrt((wx1 - wx) * (wx1 -
																						 wx) +
																		   (wy1 - wy) * (wy1 -
																						 wy) +
																		   (wz1 - wz) * (wz1 -
																						 wz))));
										r = r + (l / 0x10000) * (k * m) + 10;
										g = g + ((l / 0x100) % 256) * (k * m) + 10;
										b = b + (l % 256) * (k * m) + 10;
									}
									else
									{
										zd = 2;

									}
								}
								else
								{
									int ztp = stu.lm[p];
									if (ztp == t)
									{
										r = r + l / 0x10000;
										g = g + (l / 0x100) % 256;
										b = b + (l % 256);
									}
								}
							}
							lt++;
							bt = bt + stu.l[lt][6] * stu.l[lt][7];
						}
						ac = getP(fp, bxm - u * abxm - v * cbxm, bym - u * abym - v * cbym, 2);
						bc = getP(fp, bxm - u * abxm - v * cbxm, bym - u * abym - v * cbym, 1);
						cc = getP(fp, bxm - u * abxm - v * cbxm, bym - u * abym - v * cbym, 3);

						ac = co(ac * log((r + 1 + r1) / 5.0) / 5.0);
						bc = co(bc * log((g + 1 + g1) / 5.0) / 5.0);
						cc = co(cc * log((b + 1 + b1) / 5.0) / 5.0);

						int ym = ac * 0x10000 + bc * 0x100 + cc;
                        if (fr == 0)
                        {
                            stu.arr[draw] = ym;
                        }
                        else
                        {
                            stu.p1[draw] = ym;
                        }
					}
					if (fr == 1)
					{
						stu.lm[draw] = zt;
					}
					if (fr == 2)
					{
						ac = getP(fp, bxm - u * abxm - v * cbxm, bym - u * abym - v * cbym, 2);
						bc = getP(fp, bxm - u * abxm - v * cbxm, bym - u * abym - v * cbym, 1);
						cc = getP(fp, bxm - u * abxm - v * cbxm, bym - u * abym - v * cbym, 3);
						int ym = ac * 0x10000 + bc * 0x100 + cc;
						stu.arr[draw] = ym;
					}
					if (fr == 3)
					{
						stu.lm[draw] = t;
					}
				}
			}
			x++;
		}
		y++;
	}
	fclose(fp);
}

void f2(int n)
{
	float xm;
	float ym;
	float zm;
	int a;
	int b;
	if (n != 0)
	{
		xm = stu.l[n][1];
		ym = stu.l[n][2];
		zm = stu.l[n][3];
		a = stu.l[n][4];
		b = stu.l[n][5];
	}
	else
	{
		a = stu.a;
		b = stu.b;
		xm = stu.xb;
		ym = stu.yb;
		zm = stu.zb;
	}
	int i = 0;
	while (i < stu.m)
	{
		stu.zz[i] = 0;
		int o = 0;
		while (o < 3)
		{
			double a1 = cos(a * PI / 180);
			double a2 = sin(a * PI / 180);
			double b1 = cos(b * PI / 180);
			double b2 = sin(b * PI / 180);
			double dx = stu.x[i * 3 + o] - xm;
			double dy = stu.y[i * 3 + o] - zm;
			double dz = stu.z[i * 3 + o] - ym;
			stu.dx[i * 3 + o] = a1 * dx - a2 * dz;
			stu.dz[i * 3 + o] = a2 * dx + a1 * dz;
			stu.dy[i * 3 + o] = b1 * dy + b2 * stu.dz[i * 3 + o];
			stu.dz[i * 3 + o] = b1 * stu.dz[i * 3 + o] - b2 * dy;
			stu.zz[i] = (stu.dz[i * 3 + o] + stu.zz[i]) / 2;
			stu.sx[i * 3 + o] = xz(stu.dx[i * 3 + o], stu.dz[i * 3 + o], n);
			stu.sy[i * 3 + o] = xz(stu.dy[i * 3 + o], stu.dz[i * 3 + o], n);
			o++;
		}
		stu.su[i] = i;
		if (stu.zz[i] > 5)
		{
			stu.zu[i] = stu.zz[i] * 100;
		}
		else
		{
			stu.zu[i] = -1;
		}
		i++;
	}
	quicksort(stu.zu, 0, stu.m - 1);
	if (n == 0)
	{
		int lt = 1;
		while (lt <= stu.lt)
		{
			double a1 = cos(a * PI / 180);
			double a2 = sin(a * PI / 180);
			double b1 = cos(b * PI / 180);
			double b2 = sin(b * PI / 180);
			double dx = stu.l[lt][1] - xm;
			double dy = stu.l[lt][2] - zm;
			double dz = stu.l[lt][3] - ym;
			stu.lz[lt][1] = a1 * dx - a2 * dz;
			stu.lz[lt][3] = a2 * dx + a1 * dz;
			stu.lz[lt][2] = b1 * dy + b2 * stu.lz[lt][3];
			stu.lz[lt][3] = b1 * stu.lz[lt][3] - b2 * dy;
			lt++;
		}
	}
}

void f3()
{
	int i;
	int l;
	int lt = 1;
	if (stu.tu == 1)
	{
		stu.bt1 = stu.wh;
		while (lt <= stu.lt)
		{
			l = 0;
			i = stu.m;
			f2(lt);
			while (i >= 0 && l != -1)
			{
				int o = stu.su[i];
				Triangle(stu.sx[o * 3], stu.sy[o * 3], stu.sx[o * 3 + 1], stu.sy[o * 3 + 1],
						 stu.sx[o * 3 + 2], stu.sy[o * 3 + 2], o, stu.yt, lt);
				i--;
				l = stu.zu[i];
			}
			stu.bt1 = stu.bt1 + stu.l[lt][6] * stu.l[lt][7];
			lt++;
		}
		stu.bt1 = 0;

		f2(0);
		l = 0;
		i = stu.m;
		stu.bt1 = 0;
		while (i >= 0 && l != -1)
		{
			int o = stu.su[i];
			Triangle(stu.sx[o * 3], stu.sy[o * 3], stu.sx[o * 3 + 1], stu.sy[o * 3 + 1],
					 stu.sx[o * 3 + 2], stu.sy[o * 3 + 2], o, 0, 0);
			i--;
			l = stu.zu[i];
		}
	}
	else
	{
		f2(0);
		stu.bt1 = 0;
		i = stu.m;
		while (i >= 0 && l != -1)
		{
			int o = stu.su[i];
			Triangle(stu.sx[o * 3], stu.sy[o * 3], stu.sx[o * 3 + 1], stu.sy[o * 3 + 1],
					 stu.sx[o * 3 + 2], stu.sy[o * 3 + 2], o, 2, 0);
			i--;
			l = stu.zu[i];
		}
	}
}
void draw(int z)
{
    printf("\e[H");
    int i=1;
    while (i < stu.wh)
    {
        if (z == 0)
        {
            stu.arr[i] = -1;
        }
        else
        {
            if (stu.arr[i] == -1)
            {
                printf(" ");
            }
            else
            {
                int r = stu.arr[i] / 0x10000;
                int g = (stu.arr[i] / 0x100) % 256;
                int b = stu.arr[i] % 256;
                if(r<0){
                    r=0;
                }
                if(g<0){
                    g=0;
                }
                if(b<0){
                    b=0;
                }
                int m=(r+b+g)/(3*25);
                switch(m)
                {
                	case 1:printf(".");break;
                	case 2:printf(":");break;
                	case 3:printf(";");break;
                	case 4:printf("~");break;
                	case 5:printf("=");break;
                	case 6:printf("*");break;
                	case 7:printf("!");break;
                	case 8:printf("$");break;
                	case 9:printf("&");break;
                	case 10:printf("@");break;
                	case 11:printf("S");break;
                }
                
            }
            int ix = (i + 1) % stu.w;
            if (ix ==0)
            {
                printf("\n");
            }
        }
        i++;
    }
}
int main()
{
	stu.bi = 1;
	stu.tu = 1;
	stu.bs = 4;
	stu.s = 20;
	stu.yt = 1;
	stu.sz1 = 10;
	stu.sz2 = 1000;
	stu.fr = 0;
	stu.zb = 100;
	stu.b = 20;
	stu.xb = 0;
	stu.yb = 0;
	printf("\033[?25l");
	printf("\033[48;2;255;255;255m");
	stu.sj = 0;
	int i = 0;
	initialize();
	stu.lt = 2;
	stu.l[1][6] = 400;
	stu.l[1][7] = 400;
	stu.l[1][8] = 0;
	stu.l[1][9] = 10;
	stu.l[1][10] = 900;
	stu.l[1][11] = 0xdddddd;
	stu.l[1][12] = 100;
	stu.l[2][1] = 6;
	stu.l[2][2] = 6;
	stu.l[2][4] = -135;
	stu.l[2][5] = 90;
	stu.l[2][3] = 8;
	stu.l[2][6] = 80;
	stu.l[2][7] = 80;
	stu.l[2][8] = 0;
	stu.l[2][9] = 10;
	stu.l[2][10] = 100;
	stu.l[2][12] = 0;
	stu.l[2][11] = 0xffffff;
	stu.ft = 1;
	stu.ft1 = 0;
	int a = 0;
	f1();
	while (1)
	{
		stu.l[1][3] = 10;
		stu.l[1][1] = 100 * sin(PI * a / 180);
		stu.l[1][2] = 100 * cos(PI * a / 180);
		stu.l[1][4] = a;
		stu.l[1][5] = 170;
		stu.l[1][10] = 100;
		stu.xb = 130 * sin(PI * i / 180);
		stu.yb = 130 * cos(PI * i / 180);
		stu.zb = 10;
		draw(0);
		f3();
		draw(1);
		printf("%d", stu.m);
		stu.a = 180+i;
		stu.b = 0;
		i=i+10;
		a=45;
	}
	return 0;
}
