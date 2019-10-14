#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){

  /*VideoCapture capture;

  if(!capture.isOpened()){
    cout << "Deu pra abrir a câmera não, nego!" << endl;
    return -1;
  }
*/
  //while(1){
    // Matrizes usadas para o tratamento da imagem
    Mat frame, frameHSV, threshado, threshado2;
    //capture >> frame;   //Caso esteja usando a câmera, o frame é a captura da câmera
    frame = imread("Carai.jpg", CV_LOAD_IMAGE_COLOR);   //Caso lendo uma imagem, o frame é a imagem
    if(frame.empty())
      return -1;    //Se o frame está vazio, fudeo

    //O vermelho em HSV tem um thresh Lower e Upper
    int threshLowL[] = {0, 153, 102};     //Thresh Lower Low
    int threshHighL[] = {7, 255, 255};    //Thresh Lower High
    int threshLowU[] = {169, 153, 102};   //Thresh Upper Low
    int threshHighU[] = {180, 255, 255};  //Thresh Upper High

    cvtColor(frame, frameHSV, CV_BGR2HSV);  //Converte a imagem lida para HSV

    //Máscara para o intervalo Lower
    inRange(frameHSV, Scalar(threshLowL[0], threshLowL[1], threshLowL[2]), Scalar(threshHighL[0], threshHighL[1], threshHighL[2]), threshado);
    //Máscara para o intervalo Upper
    inRange(frameHSV, Scalar(threshLowU[0], threshLowU[1], threshLowU[2]), Scalar(threshHighU[0], threshHighU[1], threshHighU[2]), threshado2);

    //Une as duas máscaras
    bitwise_or(threshado, threshado2, threshado);

    //Para eliminar o ruído dá o erode e depois o dilate
    erode(threshado, threshado, getStructuringElement(MORPH_RECT, Size(5, 5)));
    dilate(threshado, threshado, getStructuringElement(MORPH_RECT, Size(5, 5)));

    //Colore as regiões vermelhas de Rosa
    frame.setTo(Scalar(221, 0, 255), threshado);

    //Mostra o que interessa
    namedWindow("frame Original", WINDOW_AUTOSIZE);
    imshow("frame Original", frame);
    namedWindow("frame threshado combinado", WINDOW_AUTOSIZE);
    imshow("frame threshado combinado", threshado);

    waitKey(0);

    /*char c=(char)waitKey(25);
    if(c==27)
      break;*/

  //}

  return 0;
}
