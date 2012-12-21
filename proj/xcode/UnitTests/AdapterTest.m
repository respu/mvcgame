//
//  AdapterTest.m
//  mvcgraphics
//
//  Created by Miguel Ibero on 21/12/12.
//  Copyright (c) 2012 Social Point. All rights reserved.
//

#import "AdapterTest.h"

@implementation AdapterTest

- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
    CCDirector *pDirector = CCDirector::sharedDirector();
    // turn on display FPS
    pDirector->setDisplayStats(false);
    //pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());
    
    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    //pDirector->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();
    
    // run
    //pDirector->runWithScene(pScene);
    
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testExample
{
    int result = launchAllTests();
    STAssertEquals(result, 0, @"Failed!!!");
}

@end
