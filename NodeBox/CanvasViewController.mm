#import "CanvasViewController.h"

@implementation CanvasViewController

- (id)init
{
    if (![NSBundle loadNibNamed:@"CanvasView" owner:self]) {
        NSLog(@"Could not load nib CanvasView");
    }
    return self;
}

- (NSView *)view
{
    return _view;
}

@end
