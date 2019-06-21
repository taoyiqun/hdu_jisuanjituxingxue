#include<Windows.h>
#include<GL\glut.h>
#include<cmath>

//初始化绘图函数
void    Init(void);
//绘制点
void    SetPoint(void);
//绘制线
void    SetLine(void);
//显示函数
void    display(void);
//绘制贝泽尔曲线
void    SetBezier(void);
//添加鼠标事件
void MymouseFunction(int button, int state, int x, int y);



//点类
class Point
{
public:
	float x, y;
	void SetXY(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

static int Pointsum = 0;//控制点的个数

static Point points[100];//存放控制点
static Point BezerPoints[11000];//存放计算出的生成贝泽尔曲线的点

//初始化函数
void Init(void) {
	glClearColor(1,1,1,0);
    glColor3f(0,0,1); //设置绘图颜色
    glPointSize(5.0); //设定点的大小
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,600.0,0.0,480.0); //平行投影，四个参数分别是x,y范围
	glEnable(GL_LINE_SMOOTH);

}

//绘制点
void SetPoint(Point p) {
	glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
    glFlush();
}

//绘制线
void SetLine(Point p1, Point p2) {
    glBegin(GL_LINES);
    glVertex2f(p1.x,p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
    glFlush();
}

//display函数
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

// 绘制贝塞尔曲线
void SetBezier(void) {
    	int	cnt = 0;
		float xx[100];
		float yy[100];

        for (double t = 0.0; t <= 1.0; t += 0.0001){
			for (int i = 1; i < Pointsum; i++) {
				for (int k = 0; k < Pointsum - i; k++) {
					if (i == 1) {
						xx[k] = points[k].x*(1 - t) + points[k + 1].x*t;
						yy[k] = points[k].y*(1 - t) + points[k + 1].y*t;
					}
					else{
						xx[k] = xx[k]*(1 - t) + xx[k + 1]*t;
						yy[k] = yy[k]*(1 - t) + yy[k + 1]*t;
					}
				}
			}
			BezerPoints[cnt].SetXY(xx[0], yy[0]);
			cnt++;
        }
		glColor3f(0.0, 0.0, 1.0); // 设定贝塞尔曲线的颜色
		for (int i = 0; i < cnt-1; i++) {
			SetLine(BezerPoints[i],BezerPoints[i+1]);
		}


}


void MymouseFunction(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON&&state==GLUT_DOWN) {// 如果鼠标左键按下
        points[Pointsum].SetXY(x,480- y); // 这里求鼠标点的坐标
        // 设置点的颜色，绘制点
        glColor3f(1.0,0.0,0.0);
        SetPoint(points[Pointsum]);
        // 设置线的颜色，绘制线
        glColor3f(1.0,0.0,0.0);
		if (Pointsum > 0) {
			SetLine(points[Pointsum - 1], points[Pointsum]);
		}

		if (Pointsum < 99) {
			Pointsum++;
		}
	}else if (button == GLUT_RIGHT_BUTTON&&state==GLUT_DOWN) {
		 //绘制贝塞尔曲线
			SetBezier();
			Pointsum = 0;
	}
}



int main(int argc, char *argv[]){
    glutInit(&argc, argv); //固定格式
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //缓存模式
    glutInitWindowSize(600, 480);    //显示框的大小
    glutInitWindowPosition(100, 100); //确定显示框左上角的位置
    glutCreateWindow("17042127 陶逸群");

    Init(); // 初始化
    glutMouseFunc(MymouseFunction); // 添加鼠标事件
    glutDisplayFunc(display); // 执行显示
    glutMainLoop(); //进人GLUT事件处理循环
    return 0;
}
