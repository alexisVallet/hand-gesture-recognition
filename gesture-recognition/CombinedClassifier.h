/* 
 * File:   CombinedClassifier.h
 * Author: Alexis
 *
 * Created on 6 janvier 2013, 21:05
 */

#ifndef COMBINEDCLASSIFIER_H
#define	COMBINEDCLASSIFIER_H

#include "Classifier.h"

/**
 * Classifier combining:
 * - the convexity classifier
 * - the 
 */
class CombinedClassifier : public Classifier {
public:
    CombinedClassifier();
    CombinedClassifier(const CombinedClassifier& orig);
    virtual ~CombinedClassifier();
private:

};

#endif	/* COMBINEDCLASSIFIER_H */

