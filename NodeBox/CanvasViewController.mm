#import "CanvasViewController.h"

@implementation CanvasViewController

- (id)init
{
    if (![NSBundle loadNibNamed:@"CanvasView" owner:self]) {
        NSLog(@"Could not load nib CanvasView");
    }
    NSLog(@"View self %@", _view);
    return self;
}

- (NSView *)view
{
    return _view;
}

@end
