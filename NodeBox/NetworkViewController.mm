#import "NetworkViewController.h"
#import "NetworkView.h"
@implementation NetworkViewController

- (id)init
{
    self = [super init];
    if (![NSBundle loadNibNamed:@"NetworkView" owner:self]) {
        NSLog(@"Could not load nib NetworkView");
    }
    [(NetworkView *)_view setController:self];
    return self;
}

- (NSView *)view
{
    return _view;
}



@end
