#include "ofApp.h"



class CircleFromThreePoints {
public:
    
    /// dummy
    CircleFromThreePoints(){}
    
    //typedef Basic2DVector<float>   Vector2D;
    
    /** Construct from three points (see class description).
     *  The order of points is not essential, but accuracy should be better if
     *  the second point lies between the other two on the circle.
     *  The optional argument "precision" specifies how accurately the
     *  straight line check has to be satisfied for setting the curvature
     *  to zero and the center position to "undefined".
     */
    CircleFromThreePoints( const ofPoint& inner,
                          const ofPoint& mid,
                          const ofPoint& outer,
                          double precision = 1.e-7);
    
    
    /** Returns the curvature (1/radius), in cm^(-1).
     *  The curvature is precomputed, this is just access method (takes no time).
     *  If curvature is zero the center is undefined
     *  (see description of presicion above).
     */
    float curvature() const { return theCurvature;}
    
    /** returns the position of the center of the circle.
     *  If curvature is zero, center() throws an exception to avoid use of
     *  undefined position.
     *  If the curvature is very small the position of the center will
     *  be very inaccurate.
     */
    ofPoint center() const { return theCenter; }
    
private:
    
    float    theCurvature;
    ofPoint theCenter;
    
    void init( const ofPoint& b, const ofPoint& c,
              const ofPoint& offset, double precision);
};


CircleFromThreePoints::CircleFromThreePoints( const ofPoint& inner,
                                             const ofPoint& mid,
                                             const ofPoint& outer,
                                             double precision)
{
    // move to frame where inner.x == inner.y == 0;
    ofPoint b( mid.x-inner.x, mid.y-inner.y);
    ofPoint c( outer.x-inner.x, outer.y-inner.y);
    init( b, c, ofPoint( inner.x, inner.y), precision);
}

void CircleFromThreePoints::init( const ofPoint& b, const ofPoint& c,
                                 const ofPoint& offset, double precision)
{
    double b2 = b.lengthSquared();
    double c2 = c.lengthSquared();
    
    double oX(0), oY(0);
    bool solved = false;
    if (fabs(b.x) > fabs(b.y)) {    // solve for y first
        double k = c.x/b.x;
        double div = 2*(k*b.y - c.y);
        if (fabs(div) < precision) theCurvature = 0;  // if the 3 points lie on a line
        else {
            oY = (k*b2 - c2) / div;
            oX = b2/(2*b.x) - b.y/b.x * oY;
            solved = true;
        }
    }
    else {    // solve for x first
        double k = c.y/b.y;
        double div = 2*(k*b.x-c.x);
        if (fabs(div) < precision) theCurvature = 0;  // if the 3 points lie on a line
        else {
            oX = (k*b2 - c2) / div;
            oY = b2/(2*b.y) - b.x/b.y * oX;
            solved = true;
        }
    }
    if (solved) {
        theCurvature = 1./sqrt(oX*oX + oY*oY);
        double xC = oX + offset.x;
        double yC = oY + offset.y;
        theCenter = ofPoint( xC, yC);
        //    thePhi = acos(xC/sqrt(xC*xC + yC*yC));
        
        //    if (xC<0.) thePhi = thePhi - PI;
        //    cout << setiosflags(ios::showpoint | ios::fixed);
        //
        //    cout << "CircleFromThreePoints::init curv = " << theCurvature << endl;
        //    cout << "CircleFromThreePoints::init center prime = " << oX << " " << oY << endl;
        //    cout << "CircleFromThreePoints::init offset = " << offset.x << " " << offset.y << endl;
        //    cout << "CircleFromThreePoints::init center = " << theCenter.x<< " " << theCenter.y << endl;
        //
        //    float d = sqrt(theCenter.x*theCenter.x+theCenter.y*theCenter.y);
        //    cout << "CircleFromThreePoints::init dfloat = " << setw(10) << setprecision(5) << d << endl;
        //    cout << "CircleFromThreePoints::init radius = " << 1/theCurvature << endl;
    }
}




class circle {
    public :
    ofPoint pos;
    float radius;
};

#define CLOCKWISE 1
#define COUNTERCLOCKWISE  -1


int ClockWise(vector < ofPoint > pts){
    int i,j,k;
    int count = 0;
    double z;
    int n = pts.size();
    
    if (n < 3)
        return(0);
    
    for (i=0;i<n;i++) {
        j = (i + 1) % n;
        k = (i + 2) % n;
        z  = (pts[j].x - pts[i].x) * (pts[k].y - pts[j].y);
        z -= (pts[j].y - pts[i].y) * (pts[k].x - pts[j].x);
        if (z < 0)
            count--;
        else if (z > 0)
            count++;
    }
    if (count > 0)
        return(COUNTERCLOCKWISE);
    else if (count < 0)
        return(CLOCKWISE);
    else
        return(0);
}



void traceAngleToAngle(circle & circle, ofPoint from, ofPoint to, ofPolyline & line, bool bClockwise, string name){
    
    
    vector < ofPoint > pts;
    pts.push_back(from);
    pts.push_back(circle.pos);
    pts.push_back(to);
    
    int clockwise = ClockWise(pts);
    
    ///ofDrawBitmapStringHighlight(name +  " " + (clockwise == CLOCKWISE ? "clockwise" : "counter") + " want " + (bClockwise ? "clockwise" : "counter"), circle.pos);
    
    
    ofPoint diffA = (from - circle.pos);
    ofPoint diffB = (to - circle.pos);
    
    float angleA = atan2( diffA.y, diffA.x );
    float  angleB = atan2( diffB.y, diffB.x );
    
    float angleDiff = angleB - angleA;
    if (angleDiff < -PI) angleDiff += TWO_PI;
    if (angleDiff > PI) angleDiff -= TWO_PI;
    
    if ( (clockwise == CLOCKWISE && !bClockwise) ||
        (clockwise == COUNTERCLOCKWISE && bClockwise)){
        
        
        float diff = TWO_PI - fabs(angleDiff);
        if (angleDiff > 0){
            diff *= -1;
        }
        angleDiff = diff;
    }
    //    if (angleDiff < -PI) angleDiff += TWO_PI;
    //    if (angleDiff > PI) angleDiff -= TWO_PI;
    //
    //
    //    if (det > 0 && !bClockwise){
    //
    //        if (angleDiff > 0){
    //            angleDiff = -TWO_PI + angleDiff;
    //        } else {
    //             //angleDiff = -TWO_PI + angleDiff;
    //        }
    //
    //        //angleDiff *= -1;
    //    }
    //
    //
    //    ofDrawBitmapStringHighlight(name +  " " + (bClockwise ? "clockwise" : "counter"), circle.pos);
    //
    for (int i = 0; i < 100; i++){
        float angle = angleA + (angleDiff/100.0) * i;
        line.addVertex(  circle.pos + circle.radius * ofPoint(cos(angle), sin(angle)));
    }
}



//--------------------------------------------------------------
void ofApp::setup(){

    ofSetCircleResolution(100);
    
    int nCircles = 5;
    for (int i = 0; i < nCircles; i++){
        ofPoint midPt(ofGetWidth()/2, ofGetHeight()/2);
        float angle = ofMap(i, 0, nCircles, 0, TWO_PI);
        ofPoint pt = midPt + 150 * ofPoint(cos(angle), sin(angle));
        cout << pt << endl;
        
        particleCircle p;
        p.radius = ofRandom(20,80);
        p.setInitialCondition(pt.x, pt.y, 0, 0);
        circles.push_back(p);
    }
    
    for (int i = 0; i < circles.size(); i++){
        spring s;
        s.springiness = 0.5;
        s.distance = circles[i].radius + circles[(i+1) % circles.size()].radius;
        s.particleA = (particle*) &(circles[i]);
        s.particleB = (particle*) &(circles[(i+1) % circles.size()]);
        springs.push_back(s);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    
    for (int i = 0; i < circles.size(); i++){
        circles[i].resetForce();
        circles[i].addDampingForce();
    }
    
    for (int i = 0; i < circles.size(); i++){
        
        circles[i].addAttractionForce(ofGetWidth()/2, ofGetHeight()/2, 1200, 0.2);
        
        circles[i].addRepulsionForce(mouseX, mouseY, 200, 1.2);
        
    }
    
    
    for (int i = 0; i < circles.size(); i++){
        for (int j = 0; j < i; j++){
            float totalRadius = circles[i].radius + circles[j].radius;
            circles[i].addRepulsionForce(circles[j], totalRadius*1.5, 3.6);
        }
    }
    
    for (int i = 0; i < circles.size(); i++){
        for (int j = -1; j < 1; j++){
            
            if (j == 0) continue;
            
            int j_good = i + j;
            if (j_good < 0) j_good += circles.size();
            if (j_good >= circles.size()) j_good %= circles.size();
            
            float totalRadius = circles[i].radius + circles[j_good].radius;
            
            circles[i].addRepulsionForce(circles[j_good].pos.x, circles[j_good].pos.y, totalRadius, 2.6);
            circles[j_good].addRepulsionForce(circles[i].pos.x, circles[i].pos.y, totalRadius, 2.6);
            
            //cout << i << " v  s " << j_good << endl;
            
        }
        //springs[i].update();
    }
    
    for (int i = 0; i < springs.size(); i++){
        springs[i].update();
    }
    
    
    for (int i = 0; i < circles.size(); i++){
        circles[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofBackground(0);
    
    for (int i = 0; i < circles.size(); i++){
        circles[i].radius = max(120, 30) + ( max(120, 30) * 0.9 * sin(ofGetElapsedTimef() + i*0.6));
    }
    
    for (int i = 0; i < circles.size(); i++){
        springs[i].distance = circles[i].radius + circles[(i+1) % circles.size()].radius;
    }

    ofNoFill();
    ofSetColor(255, 255, 255, 100);
    for (int i = 0; i < circles.size(); i++){
        circles[i].drawMe();
    }
    
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
    
    ofSetColor(255,255,255, 180);
    
//    for (int i = 0; i < circles.size(); i++){
//        circles[i].drawMe();
//    }

    
    
    for (int i = 0; i < springs.size(); i++){
        springs[i].draw();
    }
    
    glDisable(GL_LINE_STIPPLE);
    
    
    ofNoFill();
    
    
    ofPolyline tempLine;
    
    
    for (int i = 0; i < 4; i++){
        
        int i_m_1 = i-1;
        int i_p_1 = i+1;
        if (i_m_1 < 0) i_m_1 += circles.size();
        i_p_1 %= circles.size();
        
        circle a;
        circle b;
        circle c;
        
        a.pos = circles[i_m_1].pos;
        b.pos = circles[i].pos;
        c.pos = circles[i_p_1].pos;
        
        a.radius = circles[i_m_1].radius;
        b.radius = circles[i].radius;
        c.radius = circles[i_p_1].radius;
        
        
        traceAngleToAngle(b,a.pos,c.pos, tempLine, i %2 == 1 ? ofGetMousePressed() : !ofGetMousePressed() , "0");
        
        
    }
    
    ofPoint midPt;
    
    for (int i = 0; i < circles.size(); i++){
    
        midPt += circles[i].pos;
        
    }
    
    midPt /= (float)circles.size();
    
    float f = ofGetElapsedTimef();
    
    ofSetColor(255);
    //tempLine = tempLine.getSmoothed(3);
    //tempLine.draw();
    
    for (int i = 0; i < circles.size(); i++){
        int i_m_1 = i-1;
        int i_p_1 = i+1;
        if (i_m_1 < 0) i_m_1 += circles.size();
        i_p_1 %= circles.size();
        
        ofPoint a = circles[i_m_1].pos;
        ofPoint b = circles[i].pos;
        ofPoint c = circles[i_p_1].pos;
        
        //cout << i << " " << a << " " << b << " " << c << endl;
        CircleFromThreePoints CFT(a, midPt + (100 + i*100) * ofPoint(cos(f*3.0 + i/5.0), sin(f*1.3 + i/5.0)),b);
        
        //midPt + 100 * ofPoint(cos(f*1.7 + i/3.0), sin(f + i/3.0))
        ofPoint center = CFT.center();
        float radius = 1.0 / CFT.curvature();
        ofSetColor(255,255,255,255);
        //ofNoFill();
        //ofCircle(center, radius);
        
        
        
        
        ofSetColor(255,255,255,100);
        ofNoFill();
        ofCircle(center, radius);
        
        ofPoint diff = midPt - center;
        
        
        ofPoint diff1 = a - center;
        ofPoint diff2 = b - center;
        
        float angleA = atan2(diff1.y, diff1.x);
        float angleB = atan2(diff2.y, diff2.x);
        float angleDiff = angleB - angleA;
        while(angleDiff > PI){
            angleDiff -= TWO_PI;
        }
        while(angleDiff <-PI){
            angleDiff += TWO_PI;
        }
        
        
        
        
        //float angle = atan2(diff.y, diff.x);
        //angle += ofGetElapsedTimef();
        //float anglePre = angle - PI/2.0;
        //float anglePost = angle + PI/2.0;
        ofPolyline tempLine2;
        
        for (int j = 0; j < 100; j++){
            float angle = ofMap(j,0+20,99-20, angleA, angleA+angleDiff);
            tempLine2.addVertex( center + radius * ofPoint(cos(angle), sin(angle)));
        }
        ofSetColor(255,255,255);
        tempLine2.draw();
        
        ofPolyline tempLine3;
        
        for (int j = 0; j < 100; j++){
            float angle = ofMap(j,0+10,99-10, angleA, angleA+angleDiff);
            tempLine3.addVertex( center + (radius+ (ofSignedNoise(i*10, ofGetElapsedTimef()) * 10 + 12)) * ofPoint(cos(angle), sin(angle)));
        }
        ofSetColor(255,255,255);
        tempLine3.draw();
        
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
