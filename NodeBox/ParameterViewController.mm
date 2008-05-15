#import "ParameterViewController.h"

@implementation ParameterViewController

- (id)init
{
    if (![NSBundle loadNibNamed:@"ParameterView" owner:self]) {
        NSLog(@"Could not load nib ParameterView");
    }
    NSLog(@"View self %@", _view);
    return self;
}

- (NSView *)view
{
    return _view;
}

@end
