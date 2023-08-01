import { Component } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { ReviewService } from 'src/app/services/review.service';
import { Location } from '@angular/common';

@Component({
  selector: 'app-review-delete',
  templateUrl: './review-delete.component.html',
  styleUrls: ['./review-delete.component.css']
})
export class ReviewDeleteComponent {
  userHandle: string = "";
  productId: number = 0;
  serverResponse: String|null = null;
  constructor(
    private route: ActivatedRoute,
    private reviewService: ReviewService,
    private location: Location,
    private router: Router
  ) {}

  ngOnInit(): void {
    let userHandleString: string | null = this.route.snapshot.queryParamMap.get('user_handle');
    if(userHandleString == null) {
      return;
    }
    let productIdString: string | null = this.route.snapshot.queryParamMap.get('product_id');
    if(productIdString == null) {
      return;
    }
    this.userHandle = userHandleString;
    this.productId = parseInt(productIdString);
  }

  goBack(): void {
    this.location.back();
  }

  deleteReview(): void {
    this.reviewService.deleteReview(this.userHandle, this.productId).subscribe({
      next: response => {
        this.serverResponse="Operation was succesful!";
      },
      error: error => {
        this.serverResponse="An error occured!";
      }
    });
  }
}
