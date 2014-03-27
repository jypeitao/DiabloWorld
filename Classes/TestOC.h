#import <Foundation/Foundation.h>

@interface TestOC : UIViewController<UIWebViewDelegate>{
    UIWebView * web;
    UIActivityIndicatorView *ac;
}
-(void)test;
-(void)testWebView;
-(void)firefly;
@end
