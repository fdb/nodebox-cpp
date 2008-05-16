#import "NetworkViewController.h"

@implementation NetworkViewController

- (id)init
{
    if (![NSBundle loadNibNamed:@"NetworkView" owner:self]) {
        NSLog(@"Could not load nib NetworkView");
    }
    return self;
}

- (NSView *)view
{
    return _view;
}



@end
