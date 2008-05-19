#import <Cocoa/Cocoa.h>
#import "ViewController.h"

@interface ParameterViewController : ViewController {
    IBOutlet NSView *_view;
    IBOutlet NSTableView *tableView;
}

- (NSView *)view;

@end
