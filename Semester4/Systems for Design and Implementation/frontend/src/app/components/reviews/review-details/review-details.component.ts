import { Component } from '@angular/core';
import { ActivatedRoute, Route, Router } from '@angular/router';
import { Location } from '@angular/common';
import { Review } from 'src/app/model/Review';
import { ReviewService } from 'src/app/services/review.service';
import { LoginService } from 'src/app/services/login.service';
import { UserService } from 'src/app/services/user-service';
import { Role } from 'src/app/model/Role';

@Component({
  selector: 'app-review-details',
  templateUrl: './review-details.component.html',
  styleUrls: ['./review-details.component.css']
})
export class ReviewDetailsComponent {
  review: Review | null = null;
  loggedInUser: string = "visitor";
  role: Role | null = null;

  constructor(
    private route: ActivatedRoute, 
    private reviewService: ReviewService, 
    private location: Location,
    private router: Router,
    private activatedRoute: ActivatedRoute,
    private loginService: LoginService,
    private userService: UserService
  ) {
    
  }

  ngOnInit(): void {
    let userHandleString: string | null = this.route.snapshot.queryParamMap.get('user_handle');
    if(userHandleString == null) {
      return;
    }
    let userHandle = userHandleString;
    let productIdString: string | null = this.route.snapshot.queryParamMap.get('product_id');
    if(productIdString == null) {
      return;
    }
    let productId = parseInt(productIdString);
    this.reviewService.getReviewById(userHandle, productId).subscribe(result => {
      this.review = result;
    });
    this.loginService.getUserHandleObservable().subscribe({
      next: (value) => {
        if(value != null) {
          this.loggedInUser = value;
        }
        this.userService.getUserRole(this.loggedInUser).subscribe({
          next: (role) => {this.role = role;}
        });
      }
    });
  }

  goBack(): void {
    this.location.back();
  }
}
