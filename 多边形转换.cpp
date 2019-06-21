#include<Windows.h>
#include<GL\glut.h>
#include<cmath>
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
//边结构体
typedef struct Edge{
    float y_max,x;
    float dx;
    Edge *next;
}Edge;
static int Pointsum = 0;//多边形的点数
static float eps=1e-10;//误差，用于初始化分类边表时float和int的比较
static Point points[100];//多边形顶点

//初始化函数

void Init(void) {
	glClearColor(1,1,1,0);
    glColor3f(0,0,1); //设定绘图颜色
    glPointSize(5.0); //设定点的大小
	glMatrixMode(GL_PROJECTION); // 设定合适的矩阵
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

// 多边形填充函数
void Filling(void) {
    int MaxY = 0;
	int i;
	for (i = 0; i < Pointsum; i++){
        if (points[i].y > MaxY){
              MaxY = points[i].y;
        }
	}       //选出最大的顶点所对应的y值
	Edge *pAET = new Edge;//活化边表
	pAET->next = NULL;
	Edge *pEdge[1024];//分类边表
	for (i = 0; i <= MaxY; i++){
		pEdge[i] = new Edge;
		pEdge[i]->next = NULL;
	}//初始化活性边表
	//一个点跟前面的点形成一条线段,同时跟后面一个点形成线段
	for (i = 0; i < MaxY; i++){
	    for (int j = 0; j < Pointsum; j++){
			if (fabs(points[j].y - i)<=eps){
			    if (points[(j - 1 + Pointsum) % Pointsum].y > points[j].y){
					Edge *p = new Edge;
					p->x = points[j].x;
					p->y_max = points[(j - 1 + Pointsum) % Pointsum].y;
					p->dx = (points[(j - 1 + Pointsum) % Pointsum].x - points[j].x) / (points[(j - 1 + Pointsum) % Pointsum].y - points[j].y);
					p->next = pEdge[i]->next;
					pEdge[i]->next = p;
				}
				if (points[(j + 1 + Pointsum) % Pointsum].y > points[j].y){
				    Edge *p = new Edge;
                    p->x = points[j].x;
                    p->y_max = points[(j + 1 + Pointsum) % Pointsum].y;
                    p->dx = (points[(j + 1 + Pointsum) % Pointsum].x - points[j].x) / (points[(j + 1 + Pointsum) % Pointsum].y - points[j].y);
                    p->next = pEdge[i]->next;
                    pEdge[i]->next = p;
				}
			}
		}
	}

	//把新边表Edge[i]中的边节点用插入排序法插入AET表，使之按照x的坐标递增顺序排序
	for (i = 0; i <= MaxY; i++)
    {
		Edge *p = pAET->next;
		while (p){
			p->x = p->x + p->dx;
			p = p->next;
		}
		Edge *tq = pAET;
		p = pAET->next;
		tq->next = NULL;
		while (p){
			while (tq->next && p->x >= tq->next->x){
			    tq = tq->next;
            }//重新排序
			Edge *s = p->next;
			p->next = tq->next;
			tq->next = p;
			p = s;
			tq = pAET;
		}

		//遍历AET表，把配对交点的区间(左闭右开）上的像素(x,y)
		Edge *q = pAET;
		p = q->next;
		while (p){
			if (p->y_max == i){
				q->next = p->next;
				delete p;
				p = q->next;
			}
			else{
				q = q->next;
				p = q->next;
			}
		}
		p = pEdge[i]->next;
		q = pAET;
		while (p)
		{
			while (q->next && p->x >= q->next->x){
                q = q->next;
			}
			Edge *s = p->next;
			p->next = q->next;
			q->next = p;
			p = s;
			q = pAET;
		}
		p = pAET->next;
		glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0,1.0,0.0);
        glBegin(GL_POINTS);
		while (p && p->next){
			for (float j = p->x; j <= p->next->x; j++){
				glVertex2i(j, i);//改写像素的颜色值
			}
			p = p->next->next;
		}
	}
	glEnd();
	glFlush();
}


void MymouseFunction(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON&&state==GLUT_DOWN) {// 如果鼠标左键按下
        points[Pointsum].SetXY(x,480- y); // 这里求鼠标点的坐标的时候
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
	}else if (button == GLUT_RIGHT_BUTTON&&state==GLUT_DOWN) {//鼠标右键按下

		  glColor3f(1.0,0.0,0.0);
        SetLine(points[0], points[Pointsum-1]);

		 //填充
			Filling();
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
