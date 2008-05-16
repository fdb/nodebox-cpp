#import "ParameterViewController.h"

@implementation ParameterViewController

- (id)init
{
    if (![NSBundle loadNibNamed:@"ParameterView" owner:self]) {
        NSLog(@"Could not load nib ParameterView");
    }
    return self;
}

- (NSView *)view
{
    return _view;
}

@end
